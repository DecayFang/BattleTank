// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declaration
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	// how close can the AI tank get to our player tank
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 3000.f;

private:
	
	// reference to the aiming component set in blueprint
	UTankAimingComponent* TankAimingComponent = nullptr;
	
};
