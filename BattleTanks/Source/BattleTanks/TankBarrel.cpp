// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "BattleTanks.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Degrees Per Second: %f"), RelativeSpeed);
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

	auto ElevationChange = RelativeSpeed * MaxElevatePerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawElevationChange = FMath::Clamp(RelativeRotation.Pitch + ElevationChange,MinElevationDegrees,MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawElevationChange, 0, 0));
}
