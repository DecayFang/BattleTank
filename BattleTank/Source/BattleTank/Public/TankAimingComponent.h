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
	Aiming,			// tank's turret and barrel is moving, and the projectile is ready
	Locked			// tank is aiming towards the crosshair, and the projectile is ready
};

// Forward declarations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// do the actual aiming behavior: move the barrel of the owner tank towards the HitLocation
	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const UTankBarrel* GetBarrelReference() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// represent the tank's current firing status
	UPROPERTY(BlueprintReadOnly, category = "State")
	EFiringState FiringStatus = EFiringState::Reloading;

private:	
	// helper function that move the barrel towards the given direction
	void MoveBarrelTowards(FVector Direction);

	// reference to the barrel mesh
	UTankBarrel* Barrel = nullptr;

	// reference to the turret mesh
	UTankTurret* Turret = nullptr;
		
};
