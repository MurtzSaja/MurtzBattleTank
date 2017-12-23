// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 *
 */

class UTankTrack;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UTankMovementComponent();

	UFUNCTION(BlueprintCallable)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
		void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable)
		void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack* RightTrack = nullptr;
	UTankTrack*	LeftTrack = nullptr;


};
