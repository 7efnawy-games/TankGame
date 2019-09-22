// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Tank.generated.h"



class UTankBarrel;
class UTankTurrent;
class ASprungWheel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);//Call it as you like

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	//void AimAt(FVector HitLocation,float LaunchSpeed);//ToRemove
	
	FTankDelegate OnDeath;
	
	
	void BeginPlay()override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	 float TakeDamage(float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;
	 //Returns current Health as a percent of  the Starting Health
	 //BlueprintPure like a const
	 UFUNCTION(BlueprintPure,Category=Health)
	 float GetHealthPercent() const ;

private:
	UPROPERTY(EditDefaultsOnly)
		int32 StartingHealth=100;
	UPROPERTY(VisibleAnywhere,Category=Health)
		int32 Health;

};
