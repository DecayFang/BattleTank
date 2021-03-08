// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "SpawningComponent.h"
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include <Components/SphereComponent.h>

// Sets default values
ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;	// TODO: check if this class need to be ticking
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Placeholder = CreateDefaultSubobject<USphereComponent>(FName("Placeholder"));
	Placeholder->SetupAttachment(Spring);

	Axle = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle"));
	Axle->SetupAttachment(Placeholder);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Placeholder);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	CurrentForce += ForceMagnitude;
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (ensure(GetAttachParentActor())) {
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!ensure(BodyRoot))
			return;
		Spring->SetConstrainedComponents(BodyRoot, NAME_None, Placeholder, NAME_None);
		Axle->SetConstrainedComponents(Placeholder, NAME_None, Wheel, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PrimaryActorTick.TickGroup == TG_PostPhysics) {
		CurrentForce = 0.f;
	}
	else
		PrimaryActorTick.TickGroup = TG_PostPhysics;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Wheel->AddForce(CurrentForce * Placeholder->GetForwardVector());
}

