// Fill out your copyright notice in the Description page of Project Settings.


// To fix a bug related to the radius of the shooting
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include"Runtime/Engine/Classes/GameFramework/Actor.h"
#include"Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include"Components/StaticMeshComponent.h"
#include "TankAimingComponent.generated.h"

//Enum For Aiming States


UENUM()
enum class EFiringState :uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};
//Forward Declaration Read about it more
class AProjectile;
class UTankBarrel; //Holds barrel methods
class UTankTurrent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AimAt(FVector HitLocation, float LaunchSpeed);
	

	void SetBarrelRefrence(UTankBarrel * BarrelToSet);
	void SetTurrentRefrence(UTankTurrent* TurrentToSet);

	UFUNCTION(BluePrintCallable, Category = Setup)
	void Initialize(UTankBarrel* Barrel,UTankTurrent* Turrent);

	float GetLaunchSpeed();
	//Add SetTurrent Refrence ??!
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000.f;
	///Firing
	UFUNCTION(BlueprintCallable, Category = Input)//ToRemove
		void Fire();
	EFiringState GetFiringState() const;

	UPROPERTY(BLueprintReadOnly, Category = Ammo)
	int AmmoNUM = 2;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//Readonly properties must be initialized here
	UPROPERTY(BLueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

private:

	bool IsBarrelMoving();
	UTankBarrel* Barrel = nullptr; //Forward Decleration is a subistitute to including a file
	UTankTurrent* Turrent = nullptr;
	void MoveBarrelTowards(FVector);
	

	FVector AimDirection;
	///Firing
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile>ProjectileBluePrint; //Alternative https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html
	
													 //Local Barrel Reference for the spawning projectile
		UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;

		
};
