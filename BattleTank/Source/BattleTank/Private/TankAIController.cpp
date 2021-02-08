// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AI Tank behaviors
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank && ControlledTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);		// TODO: check if radius is in cm

		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}
}
