// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <Engine/World.h>


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto testP = GetControlledTank();
	if (!testP)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller at C++ is not possessed"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller in C++ is working %s"), *(testP->GetName()));
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		// Get world location if lintrace through crosshair.
		// If it hit the landscape :
			// Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position in pixel coordinations
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX,ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairLocationX,ViewportSizeY*CrossHairLocationY);
	
	// "De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,LookDirection)) 
	{
		//UE_LOG(LogTemp,Warning,TEXT("Look Dircetion : %s"),*LookDirection.ToString());
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	// Line-trace along that look direction , and see what we hit (up to max range)


	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation;// To be discarded	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
		
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & Hitlocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Visibility)) 
	{
		Hitlocation =HitResult.Location;
		return true;
	}
	Hitlocation = FVector(0);
	return false;
}


