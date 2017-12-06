// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}


void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileSpeed)
{
	//auto TankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();

	if (!Barrel)
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

		//UE_LOG(LogTemp, Warning, TEXT("%f : Solve found !!!"), GetWorld()->GetTimeSeconds());

		MoveTowardsAimDirection(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT("ProjectileSpeed: %f, AimDirection: %s"), ProjectileSpeed, *AimDirection.ToString());
	}

}


void UTankAimingComponent::MoveTowardsAimDirection(FVector AimDirection)
{
	FRotator CurrentRotator = Barrel->GetForwardVector().Rotation();
	FRotator DesiredRotator = AimDirection.Rotation();

	FRotator DeltaRotator = DesiredRotator - CurrentRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	Turret->RotateTurret(DeltaRotator.Yaw);
}



