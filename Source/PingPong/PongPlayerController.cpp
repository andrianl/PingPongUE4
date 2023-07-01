// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayerController.h"
#include "PongPlayer.h"
#include "Components/InputComponent.h"
#include "Net/UnrealNetwork.h"

APongPlayerController::APongPlayerController()
{
	bReplicates = true;
}

void APongPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Bind input axis for paddle movement
	//InputComponent->BindAxis("MoveRight", this, &APongPlayerController::ServerMove);
}

void APongPlayerController::ServerMove_Implementation(const float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		APongPlayer* ControlledPawn = Cast<APongPlayer>(GetPawn());
		if (ControlledPawn)
		{
			ControlledPawn->Move(Value);
		}
	}
}
