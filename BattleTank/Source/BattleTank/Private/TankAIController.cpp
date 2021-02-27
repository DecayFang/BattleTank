// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AI Tank behaviors
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius);

		TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
			TankAimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) {
		// find the component
		auto AimingComp = InPawn->FindComponentByClass<UTankAimingComponent>();
		if (ensure(AimingComp)) {
			TankAimingComponent = AimingComp;
		}

		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) {
			return;
		}
		PossessedTank->OnTankDeathDelegate.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	APawn* PlayerPawn = GetPawn();
	if (PlayerPawn) {
		GetPawn()->DetachFromControllerPendingDestroy();
	} 
}
