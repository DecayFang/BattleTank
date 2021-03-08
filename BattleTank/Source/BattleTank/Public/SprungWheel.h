// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// add the force to the wheels, using the direction of the Placeholder (because this component will not rotate)
	// multiplied by the ForceMagnitude which is between [-1,1] (negative value indicates reverse direction.)
	void AddDrivingForce(float ForceMagnitude);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Setup the constraint between the Axle and BodyRoot
	void SetupConstraint();

	// Components

	UPROPERTY(VisibleAnywhere, Category = "Suspension")
	UPhysicsConstraintComponent* Spring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Suspension")
	USphereComponent* Placeholder = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Suspension")
	UPhysicsConstraintComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Suspension")
	USphereComponent* Wheel = nullptr;

private:	
	// Snapshot of the Throttle force added to the wheel
	float CurrentForce = 0.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
