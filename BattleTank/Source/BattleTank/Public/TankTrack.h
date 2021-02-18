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

// Archtectural choice:
// player can set the throttle every time they like (SetThrottle)
// but the driving force (and sideway correction force) will only be added 
// when the tank is on the ground (OnHit & Drivetank & AddSidewayForce)

public:

	UTankTrack();

	virtual void BeginPlay() override;

	// set CurrentThrottle between -1.0 and 1.0
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Maximum force pulling the tank
	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TrackMaxDrivingForce = 60000000.f;	// 40 tonne, 10m/s2 and 100 cm every meter

private:

	// add a sideway correction force to cancel the tank's slipping issue
	void AddSidewayForce();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// push (or pull) the tank according to the CurrentThrottle
	void DriveTank();

	// Throttle value of the current frame
	float CurrentThrottle;

};
