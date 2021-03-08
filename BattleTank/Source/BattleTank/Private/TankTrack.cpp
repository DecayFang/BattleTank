 // Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawningComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp(Throttle, -1.f, 1.f);
	DriveTank(CurrentThrottle);
}

void UTankTrack::DriveTank(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	for (auto Wheel : Wheels) {
		Wheel->AddDrivingForce(ForceApplied / Wheels.Num());
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> SpawningPoints;
	GetChildrenComponents(false, SpawningPoints);
	TArray<ASprungWheel*> Wheels;
	for (auto SpawningPoint : SpawningPoints) {
		USpawningComponent* CastedSpawningPoint = Cast<USpawningComponent>(SpawningPoint);
		if (!CastedSpawningPoint)
			continue;
		ASprungWheel* Wheel = Cast<ASprungWheel>(CastedSpawningPoint->GetAttachedActor());
		if (!Wheel)
			continue;
		Wheels.Push(Wheel);
	}
	return Wheels;
}

