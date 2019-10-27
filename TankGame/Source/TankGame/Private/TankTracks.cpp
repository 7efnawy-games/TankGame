// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTracks.h"
#include"SpawnPoint.h"
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
	//OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);//What is ADD DYNAMIC
}


TArray<class ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray< ASprungWheel*> SprungArray;

	TArray< USceneComponent*>Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild)continue;

		AActor* SpawnedActorChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedActorChild);
		
		SprungArray.Add(SprungWheel);
	}

	return SprungArray;


}

void UTankTracks::SetThrottle(float Throttle)
{	

	//We Need To clamp so player can't over drive but what does that mean ??!
	Throttle = FMath::Clamp<float>(Throttle, -1, 1);
	auto ForceApplied =  Throttle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}