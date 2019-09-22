// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include"TankAimingComponent.h"
#include"Tank.h"//So We Can Implement on Death

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Aim Towards CrossHair
	AimTowardsCrossHair();
}
bool ATankPlayerController::GetVectorHitLocation(FVector& HitLocation, FVector LookDirection)
{	//Declerations
	FHitResult Hit;
	FVector CameraLocation =PlayerCameraManager->GetCameraLocation();
	FVector End = CameraLocation + LineRange * LookDirection;

	
	//Line Trace Function
	if (GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, End,
		ECollisionChannel::ECC_Camera
		))
	{
		

		HitLocation = Hit.Location;
		return true;
	}
	else
	{
		return false;
	}
}
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const
{
	//To Be Discarded
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}
const bool  ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation)
{
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation=FVector2D(ViewPortSizeX*CrossHairX,ViewPortSizeY*CrossHairY);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,  LookDirection))
	{
		//Line Trace With Channel
		return GetVectorHitLocation(HitLocation, LookDirection);
	}
	else
	{
		return false;
	}
	
}
void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossesedTank = Cast<ATank>(InPawn);
	if (ensure(PossesedTank))
	{
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
	}
}
void ATankPlayerController::OnPossesedTankDeath()
{
	//UE_LOG(LogTemp,Warning,TEXT("Player Controller Tank is Dead"))
	this->StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrossHair()
{

	
	FVector HitLocation;//OUT Paramater
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
//	UE_LOG(LogTemp,Warning,TEXT("boolean is %i"),bGotHitLocation)
	if (bGotHitLocation)
	{
			AimingComponent->AimAt(HitLocation, AimingComponent->GetLaunchSpeed());
		
	}
	else
	{
		return;
	}
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; }
	auto tankcontroller = GetPawn();
	
	AimingComponent = tankcontroller->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Player controller couldn't found aiming component in Begin play"))
	}
	
}

