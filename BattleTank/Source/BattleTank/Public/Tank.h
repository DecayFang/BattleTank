// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeathDelegate);

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
	
	// the method is called by UGameplayStatics::ApplyRadialDamage
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage() const;

	FOnTankDeathDelegate OnTankDeathDelegate;

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxHealth = 100.f;

	float Health;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

};
