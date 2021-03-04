// Fill out your copyright notice in the Description page of Project Settings.


#include "AxleWheel.h"
#include <Components/SphereComponent.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>

// Sets default values
AAxleWheel::AAxleWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Axle = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle"));
	SetRootComponent(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void AAxleWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAxleWheel::SetupConstraint()
{
	if (ensure(GetAttachParentActor())) {
		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (!ensure(BodyRoot))
			return;
		Axle->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
	}
}

// Called every frame
void AAxleWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

