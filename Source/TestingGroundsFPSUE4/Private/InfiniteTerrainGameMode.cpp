// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "Public/ActorPoolComponent.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPoolComponent>(FName("NavMeshBoundsVolume Pool"));

}


void AInfiniteTerrainGameMode::PopulateBoundsPool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator(GetWorld());

	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume* VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] - %s - Set Pool: nullptr"), *FString(__FUNCTION__), *(this->GetName()));
	if (VolumeToAdd)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] - %s - Set Pool: %s"), *FString(__FUNCTION__), *(this->GetName()), *(VolumeToAdd->GetName()));
		NavMeshBoundsVolumePool->AddActor(VolumeToAdd);
	}
}