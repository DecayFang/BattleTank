// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn 
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = Behavior)
	void Fire();

	// tank will make it's barrel to rotate towards the HitLocation
	void AimAt(FVector WorldSpaceAim);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// reference to the projectile BP class in order to spawn the projectile
	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// speed the projectile will leave from the barrel
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.f;

	// minimal interval between to tank firing
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f;

private:
	// reference to the aiming component set in blueprint
	UTankAimingComponent* TankAimingComponent = nullptr;

	// used to implement the interval of firing
	double LastReloadTime = 0.0;

};
