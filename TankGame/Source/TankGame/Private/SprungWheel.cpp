// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include"GameFrameWork/Actor.h"
// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	
	PrimaryActorTick.TickGroup =TG_PostPhysics;




	MassAxelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Mass Axel Constraint"));
	SetRootComponent(MassAxelConstraint);

	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(MassAxelConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);

	AxelWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axel Wheel Constraint"));
	AxelWheelConstraint->SetupAttachment(Axel);

	



	
}
void  ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceManitudeThisFrame += ForceMagnitude;

};
void ASprungWheel::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ON HIT %f, sisi %f"), GetWorld()->GetTimeSeconds(), TotalForceManitudeThisFrame)
		ApplyForce();
}
// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	//AttachToComponent();
	SetupConstraints();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this,&ASprungWheel::OnHit);

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
		MassAxelConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axel, NAME_None);
		AxelWheelConstraint->SetConstrainedComponents(Axel, NAME_None, Wheel, NAME_None);
	
		


	

	}
}
void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axel->GetForwardVector() * TotalForceManitudeThisFrame);
}
// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceManitudeThisFrame = 0;
	}
	
}

