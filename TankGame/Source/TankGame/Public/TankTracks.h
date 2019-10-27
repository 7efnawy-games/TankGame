// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include"SprungWheel.h"
#include "TankTracks.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	/*void BeginPlay();*/
	virtual void BeginPlay() override;
	UTankTracks();
	
	

	UFUNCTION(BluePrintCallable,Category=Input)
		void SetThrottle(float Throttle);
		//Max force Per Track in Newton
private:
	TArray<class ASprungWheel*> GetWheels() const;
	//float CurrentThrottle = 0.f;
	UPROPERTY(EditDefaultsOnly)
			float TrackMaxDrivingForce = 40000000.0;
};
