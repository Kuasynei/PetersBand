// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnchovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FindNextWaypoint.h"

EBTNodeResult::Type UFindNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	AAnchovieController* Controller = Cast<AAnchovieController>(OwnerComp.GetOwner());
	
	if (Controller != nullptr)
	{
		Controller->SegwayTest(Controller->GetPawn());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}