// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// clamp the input
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	// calculate how much degrees this frame should rotate
	float DeltaDegree = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float TargetYaw = GetRelativeRotation().Yaw + DeltaDegree;	// no need to clamp here

	SetRelativeRotation(FRotator(0.f, TargetYaw, 0.f));
}
  