// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PongPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APongPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	APongPlayerController();

	UFUNCTION(Server, Reliable)
	void ServerMove(const float Value);


protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
};
