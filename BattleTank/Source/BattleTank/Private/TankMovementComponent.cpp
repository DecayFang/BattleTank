// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

// Flow:
// AI controller calls MoveToActor, which in turn call this method
// with MoveVelocity calculated by Path Finding Algorithm, 
// so we override this method to provide our logic to get the AI tank
// move to the player with given MoveVelocity in a physical way
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we're replacing the functionality
	
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();	// these two vectors are both in world space

	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardThrow);

	float TurnThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnClockwise(TurnThrow); 
}
 