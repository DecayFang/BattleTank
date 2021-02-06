// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declaration
class ATank;

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

	ATank* GetControlledTank() const;

	// tell the tank to try to move the barrel to somewhere that a firing will cause the 
	// place covered by the CrossHair be fired
	void AimTowardsCrosshair();

private:
	// helper function: get the 3D world location covered by our 2D crosshair,
	// if we can't find that location (probably the location can't be determined or
	// is out of TraceRange), then return false and invalidate the OutHitLocation
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// get the normalized direction implied by the CrossHair, return true if the engine can get that direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	// trace a line from the camera along the LookDirection and return true if anything visable hitted
	bool GetLookVectorHitLocation(FHitResult& OutHitResult, const FVector& LookPosition, const FVector& LookDirection) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float TraceRange = 100000.f;
};
