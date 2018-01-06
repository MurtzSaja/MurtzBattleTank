// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingFroce = 400000.f;

	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewayForce();

	float CurrentThrottle = 0.f;

	void DriveTrack();
};
