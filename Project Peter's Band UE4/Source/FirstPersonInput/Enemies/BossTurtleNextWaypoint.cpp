/* Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BossTurtleNextWaypoint.h"
#include "BossTurtleController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

EBTNodeResult::Type UBossTurtleNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	ABossTurtleController* Controller = Cast<ABossTurtleController>(OwnerComp.GetOwner());

	if (Controller != nullptr)
	{
		Controller->RedirectToCharacter(Controller->GetPawn());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}*/