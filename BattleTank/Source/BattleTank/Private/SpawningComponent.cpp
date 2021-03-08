// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawningComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
USpawningComponent::USpawningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USpawningComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(AttachedActorClass))
		return;
	AttachedActor = GetWorld()->SpawnActorDeferred<AActor>(AttachedActorClass, FTransform());
	if (!ensure(AttachedActor))
		return;
	// Note: there are two ways to spawn actor at the component's place:
	// 1. Default FTransform + KeepRelativeTransform
	// 2. Component's Transform + KeepWorldTransform
	AttachedActor->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	// From source code, it seems that if the transform here is same as the one when called SpawnActorDeferred
	// then nothing happened, and if not same, then this transform will be used
	UGameplayStatics::FinishSpawningActor(AttachedActor, FTransform());
}


// Called every frame
void USpawningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* USpawningComponent::GetAttachedActor()
{
	return AttachedActor;
}

