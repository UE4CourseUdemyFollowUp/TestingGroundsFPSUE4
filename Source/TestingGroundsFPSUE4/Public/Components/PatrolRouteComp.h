// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRouteComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDSFPSUE4_API UPatrolRouteComp : public UActorComponent
{
	GENERATED_BODY()

public:
	TArray<AActor*> GetPatrolPoints() const;

private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;
};
