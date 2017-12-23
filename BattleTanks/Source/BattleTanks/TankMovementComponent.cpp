// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

UTankMovementComponent::UTankMovementComponent()
{

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
	{
		return;
	}

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIMoveIntend = MoveVelocity.GetSafeNormal();

	auto Throw = FVector::DotProduct(TankForward, AIMoveIntend);
	IntendMoveForward(Throw);


	auto Turn = FVector::CrossProduct(TankForward, AIMoveIntend).Z;
	IntendTurnRight(Turn);

	//UE_LOG(LogTemp, Warning, TEXT("%s AI move velocity: %s"), *GetOwner()->GetName(),*MoveVelocity.ToString());
}

