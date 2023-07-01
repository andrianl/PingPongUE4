// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"
#include "Components/TextBlock.h"


void UScoreWidget::SetScore(int32 PlayerScore, int32 OpponentScore)
{
	if (TextBlockPlayerScore)
	{
		TextBlockPlayerScore->SetText(FText::AsNumber(PlayerScore));
	}

	if (TextBlockOpponentScore)
	{
		TextBlockOpponentScore->SetText(FText::AsNumber(OpponentScore));
	}
}

