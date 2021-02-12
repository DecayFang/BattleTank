// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATank::Fire()
{
	const UTankBarrel* Barrel = TankAimingComponent->GetBarrelReference();
	if (!ensure(Barrel)) {
		return;
	}

	bool isReloaded = (FPlatformTime::Seconds() - LastReloadTime > ReloadTimeInSeconds);
	if (isReloaded) {
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		Projectile->Launch(LaunchSpeed);
		LastReloadTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector WorldSpaceAim)
{
	// delegate the action to the component
	if(ensure(TankAimingComponent))
		TankAimingComponent->AimAt(WorldSpaceAim, LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

