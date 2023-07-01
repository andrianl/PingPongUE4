#include "PingPongGameModeBase.h"
#include "PongPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Ball.h"
#include "PingPongHUD.h"
#include "PongPlayer.h"

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ConnectedPlayers++;

	SpawnPlayerPawn(NewPlayer);

	if (ConnectedPlayers >= 2)
	{
		StartGame();

		if (IsValid(HUD))
		{
			HUD->CloseWaitingMessage();
		}
	}
	else
	{
		// Show the WaitingWidget in the HUD
		HUD = Cast<APingPongHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (IsValid(HUD))
		{
			HUD->ShowWaitingMessage();
		}
	}
}

void APingPongGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APingPongGameModeBase, FirstPlayerScore);
	DOREPLIFETIME(APingPongGameModeBase, SecondPlayerScore);
}


void APingPongGameModeBase::StartGame()
{
	if (!bGameStarted)
	{
		bGameStarted = true;



		// Perform any necessary initialization for starting the game
		// For example, spawn the ball and reset any relevant variables


		if (IsValid(HUD))
		{
			HUD->ShowScore(FirstPlayerScore, SecondPlayerScore);
		}

		StartNewRound();
	}
}

void APingPongGameModeBase::StartNewRound_Implementation()
{

	if (bGameStarted && !bRoundStarted)
	{
		bRoundStarted = true;

		// Perform any necessary initialization for starting a new round
		// For example, reset the position of the ball and update the HUD

		if (HasAuthority())
		{
			// Spawn the ball at the desired location
			SpawnBallAtLocation();
		}
	}
}

void APingPongGameModeBase::EndRound_Implementation(uint8 PlayerScored)
{
	if (bGameStarted && bRoundStarted)
	{
		bRoundStarted = false;

		// Perform any necessary actions for ending the round
		// For example, stop the ball movement and update the HUD

			// Calculate the winning player and update the scores
		UpdateScore(PlayerScored);

		HUD = Cast<APingPongHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
		if (IsValid(HUD))
		{
			HUD->ShowScore(FirstPlayerScore, SecondPlayerScore);
		}

		if (IsValid(Ball))
		{
			Ball->Destroy();
		}

		// Start a new round after the specified delay
		GetWorldTimerManager().SetTimer(NewRoundTimerHandle, this, &APingPongGameModeBase::StartNewRound, NewRoundDelay, false);
	}
}

void APingPongGameModeBase::UpdateScore(const uint8 PlayerIndex)
{

	if (PlayerIndex == 0)
	{
		FirstPlayerScore++;
	}
	else if (PlayerIndex == 1)
	{
		SecondPlayerScore++;
	}

		// Update the HUD with the new scores
		// For example, update the score widgets or display a message on screen
}

void APingPongGameModeBase::SpawnBallAtLocation_Implementation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), BallSpawnLocationClass);

		BallSpawnLocation = FoundActor->GetActorTransform();
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		Ball = World->SpawnActor<ABall>(BallClass, BallSpawnLocation.GetLocation(), BallSpawnLocation.GetRotation().Rotator(), SpawnParams);

		// Perform any additional initialization for the spawned ball if needed
	}
}

void APingPongGameModeBase::SpawnPlayerPawn(APlayerController* PlayerController)
{
	if (IsValid(PlayerController))
	{

		AActor* FoundActor;
		FVector SpawnLocation;
		FRotator SpawnRotation;

		if (ConnectedPlayers < 2)
		{
			FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), FirstSpawnLocationClass);
			SpawnLocation = FoundActor->GetActorLocation();
			SpawnRotation = FoundActor->GetActorRotation();
		}
		else
		{
			FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), SecondSpawnLocationClass);
			SpawnLocation = FoundActor->GetActorLocation();
			SpawnRotation = FoundActor->GetActorRotation();
		}

		// Spawn the player-controlled pawn
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		APongPlayer* NewPlayerPawn = GetWorld()->SpawnActor<APongPlayer>(PlayerClass, SpawnLocation, SpawnRotation, SpawnParams);

		// Assign the spawned pawn to the player controller
		PlayerController->Possess(NewPlayerPawn);

		PlayerController->ServerCheckClientPossession();

		// Set the pawn's owner to the player controller
		NewPlayerPawn->SetOwner(PlayerController);
	}
}

