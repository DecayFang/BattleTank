// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declaration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void AimingComponentFound(UTankAimingComponent* AimingComponentRef);

	// tell the tank to try to move the barrel to somewhere that a firing will cause the 
	// place covered by the CrossHair be fired
	void AimTowardsCrosshair();

protected:
	// CrossHair's x axis location in percentage
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairXLocation = 0.5f;
	
	// CrossHair's y axis location in percentage
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrossHairYLocation = 0.33333f;

	// how far the line trace will try to go
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TraceRange = 100000.f;

private:
	// helper function: get the 3D world location covered by our 2D crosshair,
	// if we can't find that location (probably the location can't be determined or
	// is out of TraceRange), then return false and invalidate the OutHitLocation
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// get the normalized direction implied by the CrossHair, return true if the engine can get that direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	// trace a line from the camera along the LookDirection and return true if anything visable hitted
	bool GetLookVectorHitLocation(FHitResult& OutHitResult, const FVector& LookPosition, const FVector& LookDirection) const;

	// reference to the aiming component set in blueprint
	UTankAimingComponent* TankAimingComponent = nullptr;

};
