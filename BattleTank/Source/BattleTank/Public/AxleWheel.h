// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AxleWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API AAxleWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAxleWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	USphereComponent* Wheel = nullptr;

private:

	void SetupConstraint();

};
