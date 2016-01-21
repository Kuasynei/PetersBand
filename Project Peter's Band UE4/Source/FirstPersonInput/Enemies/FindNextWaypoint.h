// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AnchovieController.h"
#include "FindNextWaypoint.generated.h"
/**
 * 
 */

UCLASS()
class FIRSTPERSONINPUT_API UFindNextWaypoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};