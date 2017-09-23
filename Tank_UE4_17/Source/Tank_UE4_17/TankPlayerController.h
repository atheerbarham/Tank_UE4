// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANK_UE4_17_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public :
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:
	// Start the tank moving the barrel so that a shot would hit where the crosshair intersect the world
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocatin) const;
	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.3333f;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& Hitlocation) const;
};
