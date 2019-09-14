// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include"TankBarrel.h"
#include"TankTurrent.h"
#include"Projectile.h"


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurrent* TurrentToSet)
{
	if (BarrelToSet && TurrentToSet)
	{
		Barrel = BarrelToSet;
		Turrent = TurrentToSet;
	}
	
}
EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{

	if (!ensure(Barrel)) { return;}
	//Decelerations
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	//Calculate Velocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation,
		HitLocation, LaunchSpeed,false,0,0
		, ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{

		 AimDirection = OutLaunchVelocity.GetSafeNormal();
	//	UE_LOG(LogTemp, Warning, TEXT("firing at %s"), *AimDirection.ToString())
			auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f Aim Solution Found"), Time)
			MoveBarrelTowards(AimDirection);
			
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp,Warning,TEXT("%f No Solution Found"),Time)
	}
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel&&Turrent)) { return; }
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation(); //What Does Forward Vector means ??!
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotaor = AimRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotaor.Pitch);//TODO Remove fixed numbers 
	if (FMath::Abs(DeltaRotaor.Yaw) < 180)
	{
		Turrent->Rotate(DeltaRotaor.Yaw);
	}
	else
	{
		Turrent->Rotate(-DeltaRotaor.Yaw);
	}
	
}
float UTankAimingComponent::GetLaunchSpeed()
{
	return LaunchSpeed;
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
	
}
void UTankAimingComponent::SetBarrelRefrence(UTankBarrel* BarrelToSet)
{
	if (!ensure(BarrelToSet))return;
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurrentRefrence(UTankTurrent* TurrentToSet)
{
	if (!ensure(TurrentToSet))return;
	Turrent = TurrentToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (AmmoNUM == 0)
	{
		FiringState = EFiringState::NoAmmo;

	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		//UE_LOG(LogTemp,Warning,TEXT("LOCKED"))
		FiringState = EFiringState::Locked;
	}
}


void UTankAimingComponent::Fire()
{
	//Fire
	
	

	if (FiringState!= EFiringState::Reloading && FiringState!=EFiringState::NoAmmo)
	{
		
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBluePrint)) { return; }
		//Spawn A Projectile on the End of The Barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(GetLaunchSpeed());

		LastFireTime = FPlatformTime::Seconds();
		UE_LOG(LogTemp, Warning, TEXT("Ammo left is %i !! "),AmmoNUM)
		if (AmmoNUM > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("I AM FIRING !! "))
			AmmoNUM--;
		}
		
	}
	

}


bool UTankAimingComponent::IsBarrelMoving()
{	
	if (!ensure(Barrel))return false;

	if (Barrel->GetForwardVector().Equals(AimDirection,0.01f)) { return false; }
	else { return true; }
}
