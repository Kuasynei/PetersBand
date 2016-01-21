// Fill out your copyright notice in the Description page of Project Settings.
/*
#include "FirstPersonInput.h"
#include "AnchovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FindNextWaypoint.h"

EBTNodeResult::Type UFindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, AActor* WaypointToUpdate)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

		if (ControllerToCall != NULL)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), WaypointToUpdate);
		}
	return EBTNodeResult::Failed;
}*/