// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolRouteComp.h"

TArray<AActor*> UPatrolRouteComp::GetPatrolPoints() const
{
	return PatrolPoints;
}

