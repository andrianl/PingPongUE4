// Fill out your copyright notice in the Description page of Project Settings.


#include "PongPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/SceneComponent.h"


// Sets default values
APongPlayer::APongPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp);
}

void APongPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void APongPlayer::Move(const float Value)
{
	ServerMove(Value);
}

void APongPlayer::ServerMove_Implementation(const float Value)
{
	if (HasAuthority())
	{
		BroadcastMove(Value);
	}
}

void APongPlayer::BroadcastMove_Implementation(const float Value)
{
	const FVector MovementDirection = FVector(0.0F, Value, 0.0F) * (Speed * GetWorld()->GetDeltaSeconds());

	AddActorLocalOffset(MovementDirection);
}

// Called when the game starts or when spawned
void APongPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APongPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APongPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveRight", this, &APongPlayer::Move);

}

