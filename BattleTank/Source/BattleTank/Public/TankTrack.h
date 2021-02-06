// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	// set a throttle between -1.0 and 1.0
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Maximum force pulling the tank
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TrackMaxDrivingForce = 40000000.f;	// 40 tonne, 10m/s2 and 100 cm every meter
};
