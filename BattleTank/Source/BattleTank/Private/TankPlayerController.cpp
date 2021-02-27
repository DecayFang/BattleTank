// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		// find the component, and fire the event to tell others the component has been found
		auto AimingComp = InPawn->FindComponentByClass<UTankAimingComponent>();
		if (ensure(AimingComp)) {
			AimingComponentFound(AimingComp);
			TankAimingComponent = AimingComp;
		}

		// register the On Tank Death method to tank's event
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnTankDeathDelegate.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	// trace a sight ray
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		// if the ray hits sth on the landscape, then tell the tank to aim at that thing
		TankAimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find out the crosshair location in screen coordinates system
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// de-project that 2D location to the 3D direction of what we are aiming to
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that LookDirection, and see what we hit
		FHitResult HitResult;
		if (GetLookVectorHitLocation(HitResult, PlayerCameraManager->GetCameraLocation(), LookDirection)) {
			OutHitLocation = HitResult.Location;
			return true;
		} 
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector WorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		WorldLocation, 
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FHitResult &OutHitResult, const FVector& LookPosition, const FVector& LookDirection) const
{
	FCollisionQueryParams QueryParam(FName(""), false, GetPawn());
	FCollisionResponseParams ResponseParam;
	return GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		LookPosition,
		LookPosition + LookDirection * TraceRange,
		ECollisionChannel::ECC_Camera,
		QueryParam,
		ResponseParam
	);
}


