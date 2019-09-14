// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include"Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

class UTankAimingComponent;
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:

		

		UFUNCTION(BlueprintImplementableEvent, Category =" Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef); //Implemented in BluePrint
		
		UTankAimingComponent* AimingComponent=nullptr;
public:
	virtual void BeginPlay() override;
	virtual void Tick(float ) override;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairX=0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairY=0.25;
	
	UPROPERTY(EditDefaultsOnly)
	float LineRange = 1000000.f;
	
private:		
//TODO dsaasd
void AimTowardsCrossHair(); //Move the barrel to aim to the cross hair before shooting
const bool GetSightRayHitLocation(FVector&);
bool GetLookDirection(FVector2D , FVector& )const;
bool GetVectorHitLocation(FVector& HitLocation,FVector LookDirection);
};
