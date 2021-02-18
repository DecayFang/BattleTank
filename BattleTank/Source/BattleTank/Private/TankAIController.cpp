// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComp)) {
		TankAimingComponent = AimingComp;
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AI Tank behaviors
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank)) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
			TankAimingComponent->Fire();
	}
}
