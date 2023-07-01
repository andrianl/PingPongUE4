// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	// Create a projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(Mesh);
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 1.0f;
	ProjectileMovementComponent->Friction = 0.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// Enable infinite bounces against walls
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->BounceVelocityStopSimulatingThreshold = 0.1f;
}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ABall, Velocity, COND_None, REPNOTIFY_Always);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	//Register that function that will be called in any bounce event
	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &ABall::OnProjectileBounce);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector2D ABall::Random2DUnitVector() const
{
	const float RandomAngle = FMath::FRandRange(0.0f, 2 * PI);

	const float X = FMath::Cos(RandomAngle);
	const float Y = FMath::Sin(RandomAngle);

	return {X, Y};
}

void ABall::MoveBallInRandomDirection()
{
	ServerMoveBallInRandomDirection();
}

void ABall::ServerMoveBallInRandomDirection_Implementation()
{
	if (HasAuthority())
	{
		BroadcastMoveBallInRandomDirection();
	}
}

void ABall::BroadcastMoveBallInRandomDirection_Implementation()
{
	if (!FMath::IsNearlyZero(ProjectileMovementComponent->Velocity.Z))
	{
		const FVector2D RandomDirection = Random2DUnitVector();
		ProjectileMovementComponent->Velocity = FVector{ RandomDirection, 0.0F } *ProjectileMovementComponent->InitialSpeed;
	}
}

void ABall::OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	MoveBallInRandomDirection();
}

void ABall::OnRep_Velocity()
{
	Velocity = ProjectileMovementComponent->Velocity;
}