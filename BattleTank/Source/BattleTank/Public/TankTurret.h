// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// like TankBarrel, rotate the turret a frame's amount according to the RelativeSpeed
	// -1 stands for max anti-clockwise speed, 1 stands for max clockwise speed
	// (clockwise if we look down from above to the turret)
	void Rotate(float RelativeSpeed);

private:

	// maximum degrees the turret can ever rotate every second, 
	// param RelativeSpeed in the Rotate() method is a weight of that maximum
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 20.f;	
	
};
