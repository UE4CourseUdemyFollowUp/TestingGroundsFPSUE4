// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Terrain/Tile.h"
#include "Engine/World.h"
#include "AI/Navigation/NavigationSystem.h"
#include "DrawDebugHelpers.h"
#include "Public/ActorPoolComponent.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NavMeshBoundsOffset = FVector(2000.f, 0.f, 0.f);
	MinExtent = FVector(0.f, -2000.f, 0.f);

	MaxExtent = FVector(4000.f, 2000.f, 0.f);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();	
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	NavMeshVolumePoolComp->Return(NavMeshBoundsVolume);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, const int MinSpawn, const int MaxSpawn, const float Radius, const float MinScale, const float MaxScale)
{
	const int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for (size_t i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint;
		const float RandScale = FMath::RandRange(MinScale, MaxScale);
		const bool found = FindEmptyLocation(SpawnPoint, Radius * RandScale);
		if (found)
		{
			float RandomRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandScale);
		}
	}

}

void ATile::SetActorsPool(UActorPoolComponent* ActorPool)
{
	if (nullptr != ActorPool)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Set Pool: %s"), *FString(__FUNCTION__), *(ActorPool->GetName()));

		NavMeshVolumePoolComp = ActorPool;

		PositionNavMeshBoundsVolume();
	}
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = NavMeshVolumePoolComp->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s] - NavMeshBoundsVolume == nullptr"), *FString(__FUNCTION__));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] - NavMeshBoundsVolume received: %s"), *FString(__FUNCTION__), *(NavMeshBoundsVolume->GetName()));
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavMeshBoundsOffset);
	GetWorld()->GetNavigationSystem()->Build();
}

const bool ATile::FindEmptyLocation(FVector& OutLocation, float Radius)
{
	const FBox Bounds(MinExtent, MaxExtent);
	const uint32 MAX_ATTEMPTS = 100;

	for (int i = 0; i < MAX_ATTEMPTS; i++)
	{
		FVector CandidateLocation = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidateLocation, Radius))
		{
			OutLocation = CandidateLocation;
			return true;
		}
	}
	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, const FVector SpawnPoint, float Rotation, float Scale)
{
	AActor* Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0.f, Rotation, 0.f));
	Spawned->SetActorScale3D(FVector(Scale, Scale, Scale));
}

const bool ATile::CanSpawnAtLocation(const FVector & Location, const float Radius)
{
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult,
		GlobalLocation,
		GlobalLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);

	FColor Color;

	if (HasHit)
	{
		Color = FColor::Red;
	}
	else
	{
		Color = FColor::Green;
	}

	DrawDebugCapsule(GetWorld(), GlobalLocation, 0.f, Radius, FQuat::Identity, Color, false, 100.f, 0, 5.f);

	return !HasHit;
}

