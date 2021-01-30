// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	// straight translation of the above comment, and DeltaDegree stands for "degree this frame can move"
	float DeltaDegree = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float TargetPitch = FMath::Clamp(GetRelativeRotation().Pitch + DeltaDegree, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}
