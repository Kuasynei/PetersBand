// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "ShadowAnna/ShadowAnnaCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "SetNextTargetPoint.h"

EBTNodeResult::Type USetNextTargetPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	//Set the blackboard to make calling it easier in the future

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	//Get the ID of the key that we state in the editor
	uint8 TargetKeyID = Blackboard->GetKeyID(TargetName);

	//Get the AI so we can call a function on it
	UObject* SelfActor = Blackboard->GetValue<UBlackboardKeyType_Object>(TargetKeyID);

	//Cast it to the proper class
	AShadowAnnaCharacter* ShadowAnna = Cast<AShadowAnnaCharacter>(SelfActor);
	if (ShadowAnna)
	{
	//IF the cast works call the function
		//FVector NewTarget = ShadowAnna->SetNextTargetPoint();

		//Blackboard->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), NewTarget);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


