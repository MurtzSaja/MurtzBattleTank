// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	Aiming,
	Locked,
	Reloading
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	float BarrelDegreePersecond = 5.f;

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:

	UPROPERTY(BlueprintReadOnly)
		EFiringStatus FiringState = EFiringStatus::Reloading;

	UFUNCTION(BlueprintCallable)
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(EditDefaultsOnly)
		float ProjectileSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly)
		float FireInterval = 3.f;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile> Projectile;

private:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	FVector CurrentAimDirection;

	void MoveTowardsAimDirection(FVector AimDirection);
	bool IsBarrelMoving();
	float FireTimer = 0.f;

	bool bFire = false;
};
