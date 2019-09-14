  // Fill out your copyright notice in the Description page of Project Settings.
#include "Tank.h"
#include"Projectile.h"


#include"TankBarrel.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//Why don't we need to protect pointer in constructors
	//UE_LOG(LogTemp, Warning, TEXT("JOE: Constructor called"))
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();//NEEDED FOR BP RUN
	//UE_LOG(LogTemp, Warning, TEXT("JOE: %s Begin Play called"), *GetName())

	
}
//void ATank::AimAt(FVector HitLocation, float LaunchSpeed)
//{
//	
//	if (!ensure(TankAimingComponent)) { return; }
//	TankAimingComponent->AimAt(HitLocation,LaunchSpeed);
//	
//	
//}
//float ATank::GetLaunchSpeed()
//{
//	return LaunchSpeed;
//}



// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!ensure(PlayerInputComponent))return;
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

