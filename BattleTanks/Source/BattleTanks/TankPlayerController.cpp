// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn())
	{
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
	{
		return;
	}

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

	int32 ViewportSizeX, ViewportSizeY;

	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D CrossHairScreenPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	FColor linecolor;
	if (GetLookDirection(CrossHairScreenPosition, LookDirection))
	{

		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return true;
		}

	/*	DrawDebugLine(
			GetWorld(),
			PlayerCameraManager->GetCameraLocation(),
			PlayerCameraManager->GetCameraLocation() + (LookDirection * LineTraceRange),
			linecolor.Blue,
			false,
			0.f,
			0,
			5.f
			);*/

		/*UE_LOG(LogTemp, Warning, TEXT("Retical Location World: %s"), *LookDirection.ToString())*/
	}

	/*UE_LOG(LogTemp, Warning, TEXT("Retical Location World: %s"), *ScreenWorldDirection.ToString())*/

	//OutHitLocation = CrossHairScreenPosition;
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation; // discarded location

	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitObject;
	if (GetWorld()->LineTraceSingleByChannel(HitObject, PlayerCameraManager->GetCameraLocation(), PlayerCameraManager->GetCameraLocation() + LookDirection * LineTraceRange, ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitObject.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Line Hit:  %s"), *HitObject.GetActor()->GetName())
		return true;
	}
	return false;
}


