#include "GoalPost.h"
#include "PingPongGameModeBase.h"
#include "Ball.h"
#include "Kismet/GameplayStatics.h"

AGoalPost::AGoalPost()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AGoalPost::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AGoalPost::OnOverlapBegin);
}

void AGoalPost::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{

	ABall* Ball = Cast<ABall>(OtherActor);

	uint8 PlayerScored = 0;

	switch (PlayerPost)
	{
	case ENumPlayerPost::FirstPlayer:
		PlayerScored = 1;
		break;
	case ENumPlayerPost::SecondPlayer:
		PlayerScored = 0;
		break;
	default:
		break;
	}

	if (IsValid(Ball))
	{
		APingPongGameModeBase* CurrentGameMode = Cast<APingPongGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if (IsValid(CurrentGameMode))
		{
			CurrentGameMode->EndRound(PlayerScored);
		}
	}
}
