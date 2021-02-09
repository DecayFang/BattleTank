// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel)
		return;

	// calculate the aiming vector by the given aiming point and firing speed
	FVector OutAimDirection, StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutAimDirection, StartLocation, WorldSpaceAim, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		OutAimDirection = OutAimDirection.GetSafeNormal();
		MoveBarrelTowards(OutAimDirection);
	}
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	if (Turret == nullptr || Barrel == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("%s: can't find reference to Turret or Barrel"), *GetOwner()->GetName());
		return;
	}

	// get the difference between the direction we want to aim the one that the barrel is actually aiming at
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DirectionRotator = Direction.Rotation();
	auto DeltaRotator = DirectionRotator - BarrelRotator;

	// move the turret and the barrel the right amount this frame
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}
 

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

