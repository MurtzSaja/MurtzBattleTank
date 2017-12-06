// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 4000.f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	class ATank* GetControlledTank() const;

	private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector LookDirection,FVector&) const;
};
