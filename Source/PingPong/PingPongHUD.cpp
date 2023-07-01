// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPongHUD.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"
#include "Net/UnrealNetwork.h"

void APingPongHUD::DrawHUD()
{
	Super::DrawHUD();

	// Nothing to draw in C++ since the widgets are implemented in Blueprint
}

void APingPongHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongHUD, ScoreWidgetInstance);
}

void APingPongHUD::ShowWaitingMessage()
{
	if (IsValid(WaitingWidgetClass))
	{
		WaitingWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WaitingWidgetClass);
		if (IsValid(WaitingWidgetInstance))
		{
			WaitingWidgetInstance->AddToViewport();
		}
	}
}

void APingPongHUD::CloseWaitingMessage()
{
	if (IsValid(WaitingWidgetInstance))
	{
		WaitingWidgetInstance->RemoveFromViewport();
		WaitingWidgetInstance = nullptr;
	}
}

void APingPongHUD::ShowScore(int32 PlayerScore, int32 OpponentScore)
{
	if (IsValid(ScoreWidgetClass))
	{
		if (!IsValid(ScoreWidgetInstance))
		{
			ScoreWidgetInstance = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
			ScoreWidgetInstance->AddToViewport();
		}

		if (IsValid(ScoreWidgetInstance))
		{
			ScoreWidgetInstance->SetScore(PlayerScore, OpponentScore);
		}
	}
}
