// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

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

	// try to make the barrel of the controlled tank to move to the crosshair
	void AimTowardsCrosshair();

private:
	// helper function: get the 3D world location covered by our 2D crosshair
	// it was as if that we are trace a line from our camera to that location
	// if that location is on the landscape, then return true
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	// get the direction implied by our aiming point
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	// trace a line from the %% along the LookDirection and return true if anything visable hitted
	bool GetLookVectorHitLocation(FHitResult& OutHitResult, const FVector& LookPosition, const FVector& LookDirection, float TraceRange = 100000.f) const;

protected:
	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnyWhere)
	float CrossHairYLocation = 0.33333f;

};
