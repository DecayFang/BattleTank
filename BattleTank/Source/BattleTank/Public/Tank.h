// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// propagate the reference from the editor to the component
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// tank will make it's barrel to rotate towards the HitLocation
	void AimAt(FVector WorldSpaceAim);
	
	// speed the projectile where leave from the barrel
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.f;	// TODO: find a more reasonable default LuanchSpeed

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Aiming component member that will do the actual aiming behavior
	UTankAimingComponent* TankAimingComponent = nullptr;

private:


};
