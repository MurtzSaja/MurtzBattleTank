// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		ControlledTank->Fire();
	}

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AI Possessing Tank: %s"), *GetControlledTank()->GetName()).
}

void ATankAIController::AimAt(FVector)
{
	//UE_LOG(LogTemp, Warning, TEXT("Player Possessing Tank: %s"), *GetPlayerControlledTank()->GetName())
}

//ATank* ATankAIController::GetControlledTank() const
//{
//	return;
//}

//ATank * ATankAIController::GetPlayerControlledTank() const
//{
//	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
//}
