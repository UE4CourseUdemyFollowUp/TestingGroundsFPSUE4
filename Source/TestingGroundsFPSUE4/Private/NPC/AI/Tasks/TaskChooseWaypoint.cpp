// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/NPC/AI/Tasks/TaskChooseWaypoint.h"
#include "AIController.h"
#include "Public/NPC/Components/PatrolRouteComp.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UTaskChooseWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();
	if (!ensure(AIController))
	{
		return EBTNodeResult::Aborted;
	}

	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRouteComp>();

	if (!ensure(PatrolRouteComp))
	{
		return EBTNodeResult::Aborted;
	}
	auto PatrolPoints = PatrolRouteComp->GetPatrolPoints();

	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Patrol route is empty"));
		return EBTNodeResult::Failed;
	}


	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	UE_LOG(LogTemp, Warning, TEXT("Index : %i"), Index);

	return EBTNodeResult::Succeeded;
}

