// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	auto TankName = GetName();

	bFire = (FPlatformTime::Seconds() - FireTimer) > FireInterval;

	if (Barrel && bFire)
	{

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		projectile->Launch(ProjectileSpeed);

		//bFire = false;
		FireTimer = FPlatformTime::Seconds();
	}


}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, ProjectileSpeed);
	//auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("TankName: %s, HitLocation: %s"), *TankName, *HitLocation.ToString());

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (FireTimer >= FireInterval)
	{
		bFire = true;
	}
	else
	{
		FireTimer += GetWorld()->DeltaTimeSeconds;
	}*/
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

