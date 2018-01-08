// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	FireTimer = FPlatformTime::Seconds();
	// ...

}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - FireTimer) < FireInterval)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}

}

void UTankAimingComponent::Fire()
{

	if (FiringState != EFiringStatus::Reloading)
	{
		if (!ensure(Barrel))
		{
			return;
		}

		if (!ensure(Projectile))
		{
			return;
		}
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		projectile->Launch(ProjectileSpeed);

		FireTimer = FPlatformTime::Seconds();
	}

}

EFiringStatus UTankAimingComponent::GetFiringState()
{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	//auto TankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	if (!ensure(Barrel))
	{
		return;
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("Projectile");


	bool bIsSucces = UGameplayStatics::SuggestProjectileVelocity(

		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		ProjectileSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if (bIsSucces)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		CurrentAimDirection = AimDirection;
		MoveTowardsAimDirection(AimDirection);
	}

}


void UTankAimingComponent::MoveTowardsAimDirection(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}

	FRotator CurrentRotator = Barrel->GetForwardVector().Rotation();
	FRotator DesiredRotator = AimDirection.Rotation();

	FRotator DeltaRotator = DesiredRotator - CurrentRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotator.Yaw);
	}
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}

	auto BarrelAimDirection = Barrel->GetForwardVector();

	return !BarrelAimDirection.Equals(CurrentAimDirection, 0.01f);

}


