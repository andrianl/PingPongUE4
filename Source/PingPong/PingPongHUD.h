// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PingPongHUD.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongHUD : public AHUD
{
	GENERATED_BODY()

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void DrawHUD() override;

	UFUNCTION(BlueprintCallable, Category = "PingPongHUD")
	void ShowWaitingMessage();

	UFUNCTION(BlueprintCallable, Category = "PingPongHUD")
	void CloseWaitingMessage();

	UFUNCTION(BlueprintCallable, Category = "PingPongHUD")
	void ShowScore(int32 PlayerScore, int32 OpponentScore);

	//UFUNCTION(Server, Reliable, WithValidation)
	//void ServerShowScore(int32 PlayerScore, int32 OpponentScore);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingPongHUD", Replicated)
	TSubclassOf<class UScoreWidget> ScoreWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PingPongHUD")
	TSubclassOf<UUserWidget> WaitingWidgetClass;


private:
	UPROPERTY(Transient, Replicated)
	UScoreWidget* ScoreWidgetInstance;

	UPROPERTY()
	UUserWidget* WaitingWidgetInstance;
};
