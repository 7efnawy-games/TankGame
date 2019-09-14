// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	

	
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank= (GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{	
		auto ControllerTank = (GetPawn());
		AimingComponent = ControllerTank->FindComponentByClass<UTankAimingComponent>();

		//Move Towards the Player

		MoveToActor(PlayerTank, AcceptanceRadius);//TODO Check Radius is in cm
		//Aim At
		auto AimingPosition = PlayerTank->GetActorLocation() + FVector(0, 0, PlayerTank->GetActorLocation().Z + 5.0f);
	AimingComponent->AimAt(AimingPosition,AimingComponent->GetLaunchSpeed());
	

	//If aiming or locked then Fire
	if (AimingComponent->GetFiringState() == EFiringState::Locked|| AimingComponent->GetFiringState() == EFiringState::Reloading)//To change to locked only
	{
		AimingComponent->Fire();
	}

	//Fire
		//Limit Firing
	}
}
