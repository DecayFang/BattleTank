// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
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
