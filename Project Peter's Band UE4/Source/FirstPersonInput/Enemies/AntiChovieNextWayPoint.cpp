// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AntiChovieNextWayPoint.h"
#include "AntichovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


EBTNodeResult::Type UAntiChovieNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	AAntichovieController* Controller = Cast<AAntichovieController>(OwnerComp.GetOwner());

	if (Controller != nullptr)
	{
		Controller->RedirectToCharacter(Controller->GetPawn());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}