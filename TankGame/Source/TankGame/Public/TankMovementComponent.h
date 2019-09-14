// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"
class UTankTracks;
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	 UTankMovementComponent();
	 UFUNCTION(BluePrintCallable,Category=Input)
	void IntendMoveForward(float Throw);
	 UFUNCTION(BluePrintCallable, Category = Input)
	 void IntendMovebackward(float Throw);

	 UFUNCTION(BluePrintCallable, Category = Input)
	 void IntendTurnRight(float Throw);

	 UFUNCTION(BluePrintCallable, Category = Input)
	 void IntendTurnLeft(float Throw);

	 UFUNCTION(BluePrintCallable,Category=Setup)
	 void Initialize(UTankTracks* LeftTrack, UTankTracks* RightTrack);
	 UTankTracks* LeftTrack=nullptr;
	 UTankTracks* RightTrack= nullptr;
	 
private:
	 virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
