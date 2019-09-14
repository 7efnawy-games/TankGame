// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurrent.h"

void UTankTurrent::Rotate(float RelativeSpeed)
{
	//Add Current Barrel Rotation to the Aim Direction 
	//Maybe Do animation just like we did with the door in Escape Game
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSec * GetWorld()->GetDeltaSeconds();
	auto RawRotationChange = RelativeRotation.Yaw + RotationChange;
	
	SetRelativeRotation(FRotator(0, RawRotationChange, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Barrel Roate Called"))
}