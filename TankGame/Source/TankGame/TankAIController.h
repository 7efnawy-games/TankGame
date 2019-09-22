// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include"Engine/World.h"
#include"Engine/Classes/GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	
	virtual void Tick(float) override;
	virtual void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;
	
public:
	UTankAimingComponent* AimingComponent = nullptr;
	UPROPERTY(EditAnyWhere, Category = Settings)
		float AcceptanceRadius = 30000.f;//How Close Can the AI Tank Get
	
	UFUNCTION()
	void OnPossesedTankDeath();
	 

};
