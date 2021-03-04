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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
