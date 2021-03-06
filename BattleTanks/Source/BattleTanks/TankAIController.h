// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */

class ATank;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay()override;

protected:

	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 0.f;
};
