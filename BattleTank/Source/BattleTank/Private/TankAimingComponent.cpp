// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	// calculate the difference between barrel's current rotation and Direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DirectionRotator = Direction.Rotation();
	auto DeltaRotator = DirectionRotator - BarrelRotator;

	// move the barrel the right amount this frame, given a max elevation speed, and the frame time
	Barrel->Elevate(5);	 // TODO: work out the magic number
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

