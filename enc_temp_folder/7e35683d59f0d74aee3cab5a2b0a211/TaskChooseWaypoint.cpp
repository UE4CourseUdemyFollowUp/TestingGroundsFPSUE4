// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGroundsFPSUE4/Public/AI/Tasks/TaskChooseWaypoint.h"
#include "AIController.h"
#include "Components/PatrolRouteComp.h"
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


	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	UE_LOG(LogTemp, Warning, TEXT("Index : %i"), Index);

	return EBTNodeResult::Succeeded;
}

