// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::AddSidewayForce()
{
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -GetOwner()->GetActorRightVector() * SlippageSpeed / DeltaTime;
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration / 2;	// F = ma, divided by 2 is because a tank have two tracks and this function should be called twice every frame
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: if clamp to [-1,1], tank forward turning will slow down the tank's speed
	// find a sensible way to handle that issue while ensure tank will not overdriving
	// through turing
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::DriveTank()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTank();
	AddSidewayForce();
	CurrentThrottle = 0.f;	// when player release the movement key, the Throttle will leave unchanged, and tank keep moving
}
