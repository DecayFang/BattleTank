// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "..\Public\TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s Controlling %s"),
			*GetName(), *ControlledTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s doesn't Controll anything"), *GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
		return;

	// trace a sight ray
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) {
		// if the ray hits sth on the landscape, then move the barrel towards it
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
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

bool ATankPlayerController::GetLookVectorHitLocation(FHitResult &OutHitResult, const FVector& LookPosition, const FVector& LookDirection, float TraceRange) const
{
	FCollisionQueryParams QueryParam(FName(""), false, GetControlledTank());
	FCollisionResponseParams ResponseParam;
	return GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		LookPosition,
		LookPosition + LookDirection * TraceRange,
		ECollisionChannel::ECC_Visibility,
		QueryParam,
		ResponseParam
	);
}


