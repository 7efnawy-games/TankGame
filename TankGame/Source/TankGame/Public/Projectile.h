// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include"Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include"Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include"Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/DamageType.h"
#include "TimerManager.h"
#include "Projectile.generated.h"


UCLASS()
class TANKGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//UNFUNCTION is very important because it says to the compiler that this is not a normal user defined function
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void LaunchProjectile(float);

private:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere,Category=Component)
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Component)
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Component)
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = Component)
		URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float DestroyDelay=10.f;
	UPROPERTY(EditDefaultsOnly,Category=Setup)
		float ProjectileDamage = 20.f;
	
	//Functions
	void OnTimerExpire();
	
	//void FTimerManager::SetTimer<UserClass>(FTimerHandle & InOutHandle, UserClass * InObj, typename FTimerDelegate::TUObjectMethodDelegate_Const<UserClass>::FMethodPtr InTimerMethod, float InRate, bool InbLoop = false, float InFirstDelay = -1.f)

};
