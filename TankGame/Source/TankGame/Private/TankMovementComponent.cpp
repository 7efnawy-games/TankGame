// Fill out your copyright notice in the Description page of Project Settings.
#include "TankMovementComponent.h"
#include"TankTracks.h"

void UTankMovementComponent::Initialize(UTankTracks* LeftTrackToSet, UTankTracks* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	else
	{
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}
void UTankMovementComponent::IntendMoveForward(float Throw)
{	
	//TODO Protect Pointers before using left and right track
	
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	//TODO Prevent Double Speed
}
void UTankMovementComponent::IntendMovebackward(float Throw)
{

	

	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(-Throw);
	//TODO Prevent ZeroSpeed
}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}
 void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{		
	
	 auto TankName = GetOwner()->GetName();
	 auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	 auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	 //UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s "), *TankName, *AIForwardIntention.ToString())

	 float PercentageofParallelness = FVector::DotProduct(TankForward, AIForwardIntention);
	 FVector ResultingVector = FVector::CrossProduct(TankForward, AIForwardIntention); 
	 
	 
	 if (PercentageofParallelness > 0) {
		 IntendMoveForward(PercentageofParallelness);
	 }
	 else
	 {
		 IntendMovebackward(-PercentageofParallelness);
	 }
	 if (ResultingVector.Z > 0)
	 {
		 IntendTurnRight(ResultingVector.Z);
	 }
	 else
	 {
		 IntendTurnLeft(-ResultingVector.Z);
	 }
}
UTankMovementComponent::UTankMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}
