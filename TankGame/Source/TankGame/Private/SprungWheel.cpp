// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include"GameFrameWork/Actor.h"
// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	
	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(MassWheelConstraint);



	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(MassWheelConstraint);

	
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	//AttachToComponent();
	SetupConstraints();

}
void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	else {
		UE_LOG(LogTemp, Warning, TEXT("Parent Actor is %s"), *GetRootComponent()->GetOwner()->GetName())
		//GetAttachParentActor()->GetRootComponent()
			UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!BodyRoot) { return; }
		
		//To Fix That Bug
		FVector SpawnLocation= GetRootComponent()->GetAttachParent()->GetComponentLocation();
		MassWheelConstraint->SetWorldLocation(SpawnLocation);
		Wheel->SetWorldLocation(SpawnLocation - FVector(0, 0, 150.0));

		MassWheelConstraint->SetConstrainedComponents(Wheel, NAME_None, BodyRoot, NAME_None);

	}
}
// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

