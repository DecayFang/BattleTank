// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim)
{
	if (!ensure(Barrel)) {
		return;
	}

	// calculate the aiming vector by the given aiming point and firing speed
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, DirectionToAim, StartLocation, WorldSpaceAim, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		DirectionToAim = DirectionToAim.GetSafeNormal();
		MoveBarrelTowards(DirectionToAim);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint) || RemainAmmo <= 0) {
		return;
	}
	
	if (FiringState != EFiringState::Reloading) {
		--RemainAmmo;
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->Launch(LaunchSpeed);
		LastReloadTime = FPlatformTime::Seconds();
		FiringState = EFiringState::Reloading;
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

	// TODO: if put this initialization into BeginPlay, then AI tank will shoot unconditionally at the begin play
	// sort out the reason of this issue
	LastReloadTime = FPlatformTime::Seconds();	// we cannot fire at the begining
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction)
{
	if (!ensure(Turret != nullptr && Barrel != nullptr)) {
		return;
	}

	// get the difference between the direction we want to aim the one that the barrel is actually aiming at
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto DirectionRotator = Direction.Rotation();
	auto DeltaRotator = DirectionRotator - BarrelRotator;
	if (DeltaRotator.Yaw > 180.f)	// force the turret to find the closest path
		DeltaRotator.Yaw -= 360.f;
	else if (DeltaRotator.Yaw < -180.f)
		DeltaRotator.Yaw += 360.f;

	// move the turret and the barrel the right amount this frame
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

// TODO: if SuggestProjectileVelocity() cannot suggest a valid direction
// then DirectionToAim might be in invalid state. Handle that situation in
// AimAt(), and find (or create) a reasonable EFiringState for this case
bool UTankAimingComponent::IsBarrelMoving() const
{
	check(Barrel);
	return !DirectionToAim.Equals(Barrel->GetForwardVector(), 0.02f);
}
 

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// switch the firing state
	if (RemainAmmo <= 0) {
		FiringState = EFiringState::Exhausted;
	}
	else if (FPlatformTime::Seconds() - LastReloadTime < ReloadTimeInSeconds) {
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetRemainAmmo() const
{
	return RemainAmmo;
}

