// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"
//void UTankTracks::BeginPlay()
//{
//	Super::BeginPlay();
//	UStaticMesh TrackMesh=SearchTrac
//	this->SetStaticMesh()
//}
UTankTracks::UTankTracks()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	//Signautre 
		 //DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams( FComponentHitSignature, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit );

}
void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);//What is ADD DYNAMIC
}
void UTankTracks::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Drive Tracks
	
	//Apply Sideways force
	
	
	ApplySidewaysForce();
	
}


void UTankTracks::ApplySidewaysForce()
{
	
	//Calculate the Slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Workout the Required acceleration t
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectingAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector(); //What Does that mean ?!
																				   //Apply Sideway Force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (!TankRoot)return;
	auto CorrectionForce = (TankRoot->GetMass() * CorrectingAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);

}

void UTankTracks::SetThrottle(float Throttle)
{	

	//We Need To clamp so player can't over drive but what does that mean ??!
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}