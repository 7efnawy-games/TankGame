// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
void UTankBarrel::Elevate(float RelativeSpeed)
{
	//GetBarrel Rotation 
			//Add Current Barrel Rotation to the Aim Direction 
			//Maybe Do animation just like we did with the door in Escape Game
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->GetDeltaSeconds();
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation=FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
	//UE_LOG(LogTemp,Warning,TEXT("Barrel Elevate Called"))
}
