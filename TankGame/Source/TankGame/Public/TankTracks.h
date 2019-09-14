// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

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
	
	void ApplySidewaysForce();

	UFUNCTION(BluePrintCallable,Category=Input)
		void SetThrottle(float Throttle);
		//Max force Per Track in Newton
private:
	
	float CurrentThrottle = 0;
	UPROPERTY(EditDefaultsOnly)
			float TrackMaxDrivingForce = 40000000.0;
		UFUNCTION()
			void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
