// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include <Engine/World.h>


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto testP = GetPlayerTank();
	if (!testP)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller can't find Player Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found PlayerTank -  %s"), *(testP->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if(GetPlayerTank())
	{
		// TODO Move towards the player

		// Aim towards the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		// Fire if ready
	}
	
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank is not found"));
	}
	else
	{
		return Cast<ATank>(PlayerPawn);
	}
	
	return nullptr;
}
