// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include"TankAimingComponent.h"
#include"Tank.h"//So We Can Implement on Death


void ATankAIController :: SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }

		//TODO Subscribe to tank on Death Event "Observer Pattern"
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}
void ATankAIController::OnPossesedTankDeath()
{
//	UE_LOG(LogTemp,Warning,TEXT("We Are Recieving"))
	auto PossesedTank =(GetPawn());
	if(ensure(PossesedTank))
	PossesedTank->DetachFromControllerPendingDestroy();

}
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
		auto AimingPosition = PlayerTank->GetActorLocation();
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
