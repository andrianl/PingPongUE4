// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GoalPost.generated.h"

UENUM(BlueprintType)
enum class ENumPlayerPost : uint8
{
	FirstPlayer    UMETA(DisplayName = "FirstPlayer"),
	SecondPlayer   UMETA(DisplayName = "SecondPlayer"),
};

UCLASS()
class PINGPONG_API AGoalPost : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AGoalPost();

	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(EditInstanceOnly)
	ENumPlayerPost PlayerPost;
};
