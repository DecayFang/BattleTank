// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// enumerator for firing status
UENUM()
enum class EFiringState : uint8
{
	Reloading,		// tank is preparing for new projectiles
	Aiming,			// tank's turret and/or barrel is moving, and the projectile is ready
	Locked,			// tank is aiming towards the crosshair, and the projectile is ready
	Exhausted		// tank has ran out of ammo
};

// Forward declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// do the actual aiming behavior: move the barrel of the owner tank towards the HitLocation
	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Firing State")
	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = "Firing State")
	int32 GetRemainAmmo() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// reference to the projectile BP class in order to spawn the projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// represent the tank's current firing status
	EFiringState FiringState = EFiringState::Reloading;

	// speed the projectile will leave from the barrel
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.f;

	// minimal interval between to tank firing
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.f;

	// the default value of this data indicating the initial ammo
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RemainAmmo = 50;

private:	

	void MoveBarrelTowards(FVector Direction);		// helper function

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	// used to implement the interval of firing
	double LastReloadTime = 0.0;

	// direction the tank want to aim to, this member is used to implement the crosshair state switching logic
	// TODO: there is a race condition between the Tick function of this class and the Tank AI controller class's
	// if this class's firstly get called, since FVector is default in (0,0,0), the AI tank will shoot unconditionally
	// if the LastReloadTime messed up and AI tank initally aim towards (0,0,0)
	FVector DirectionToAim;

	bool IsBarrelMoving() const;
		
};
