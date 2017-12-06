// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

UTankMovementComponent::UTankMovementComponent()
{

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %f"), Throw);
	
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
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
