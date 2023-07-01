// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * Score widget for displaying player and opponent scores.
 */
UCLASS()
class PINGPONG_API UScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    /** Set the score values to update the UI. */
    UFUNCTION(BlueprintCallable, Category = "Score Widget")
     void SetScore(int32 PlayerScore, int32 OpponentScore);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
     class UTextBlock* TextBlockPlayerScore;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
      class UTextBlock* TextBlockOpponentScore;
};
