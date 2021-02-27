// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class URadialForceComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Launch(float Speed);

protected:
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UStaticMeshComponent* CollisionMesh = nullptr;

	// handles the particle effects when a projectile leaves the barrel
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* LaunchBlast = nullptr;

	// handles the particle effects when a projectile hits something
	UPROPERTY(VisibleAnywhere, Category = "Particle")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Destroy")
	float DestroyDelay = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float ProjectileDamage= 20.f;
	 
private:

	FTimerDynamicDelegate TimerDelegate;

	void OnTimerExpire(void);

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

};
