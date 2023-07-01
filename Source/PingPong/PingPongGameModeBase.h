#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PingPongGameModeBase.generated.h"

UCLASS()
class PINGPONG_API APingPongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
		void StartGame();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void StartNewRound();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void EndRound(const uint8 PlayerScored);

	UFUNCTION(BlueprintCallable)
	void UpdateScore(const uint8 PlayerIndex);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SpawnBallAtLocation();

	// Function to spawn the player-controlled pawn
	void SpawnPlayerPawn(APlayerController* PlayerController);

protected:
	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 FirstPlayerScore = 0;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 SecondPlayerScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> FirstSpawnLocationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SecondSpawnLocationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> BallSpawnLocationClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APongPlayer> PlayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABall> BallClass;

private:
	class APingPongHUD* HUD = nullptr;

	UPROPERTY()
	ABall* Ball = nullptr;

	bool bGameStarted = false;
	bool bRoundStarted = false;
	int32 ConnectedPlayers = 0;

	FTimerHandle NewRoundTimerHandle;
	float NewRoundDelay = 3.0f; // Delay in seconds before starting a new round


	FTransform FirstSpawnLocation;

	FTransform SecondSpawnLocation;

	FTransform BallSpawnLocation;
};
