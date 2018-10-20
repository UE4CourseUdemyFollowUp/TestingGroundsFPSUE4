// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPoolComponent;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


UCLASS()
class TESTINGGROUNDSFPSUE4_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavMeshBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, const int MinSpawn, const int MaxSpawn, const float Radius, float MinScale = 1.f, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceAIActors(TSubclassOf<APawn> ToSpawn, const int MinSpawn, const int MaxSpawn, const float Radius);

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetActorsPool(UActorPoolComponent* ActorPool);

private:

	void PositionNavMeshBoundsVolume();

	TArray<FSpawnPosition> GenerateSpawnPositions(const int MinSpawn, const int MaxSpawn, const float &MinScale, const float &MaxScale, const float &Radius);

	const bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, const float& Radius = 500.f, const float& MinScale = 1.f, const float& MaxScale = 1.f);

	// Pass controller class?
	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, const FSpawnPosition SpawnPosition);

	const bool CanSpawnAtLocation(const FVector& Location, const float Radius) const;

	UActorPoolComponent* NavMeshVolumePoolComp;	

	AActor* NavMeshBoundsVolume;
};
