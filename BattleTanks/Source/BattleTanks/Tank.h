// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UStaticMeshComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
		void Fire();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly)
		float ProjectileSpeed = 4000.f;

	UPROPERTY(EditDefaultsOnly)
		float FireInterval = 3.f;

	void AimAt(FVector);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UTankAimingComponent* TankAimingComponent = nullptr;

	//UPROPERTY(BlueprintReadOnly)
	//class UTankMovementComponent* TankMovementComponent = nullptr;

private:
	UTankBarrel* Barrel = nullptr;

	float FireTimer = 0.f;

	bool bFire = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
