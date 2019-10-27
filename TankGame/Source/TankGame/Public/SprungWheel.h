// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"//TO Remove
#include "Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class TANKGAME_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AddDrivingForce(float ForceMagnitude);
	float TotalForceManitudeThisFrame = 0;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ApplyForce();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetupConstraints();
	UPROPERTY(VisibleAnywhere, Category = Component)
		USphereComponent* Wheel= nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
		USphereComponent* Axel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UPhysicsConstraintComponent* MassAxelConstraint= nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	UPhysicsConstraintComponent* AxelWheelConstraint = nullptr;

	
	

};
