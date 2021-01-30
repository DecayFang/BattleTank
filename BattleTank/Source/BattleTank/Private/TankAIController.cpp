// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s have found %s"),
				*GetName(), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%s didn't find anything"), *GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AI Tank behaviors
	auto PlayerTank = GetPlayerTank();
	auto ControlledTank = GetControlledTank();
	if (PlayerTank && ControlledTank) {
		// TODO: move to PlayerTank

		// AimAt PlayerTank
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// TODO: Fire if ready

	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController == nullptr)
		return nullptr;
	else
		return Cast<ATankPlayerController>(PlayerController)->GetControlledTank();
}
