// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPoolComponent;

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


	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetActorsPool(UActorPoolComponent* ActorPool);

private:

	void PositionNavMeshBoundsVolume();

	const bool FindEmptyLocation(FVector& OutLocation, float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, const FVector SpawnPoint, float Rotation, float Scale);

	const bool CanSpawnAtLocation(const FVector& Location, const float Radius);

	UActorPoolComponent* NavMeshVolumePoolComp;	

	AActor* NavMeshBoundsVolume;
};
