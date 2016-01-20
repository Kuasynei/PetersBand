// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Player/PlayerCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "FindPlayerTask.h"

EBTNodeResult::Type UFindPlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!GetWorld())
	{
		return EBTNodeResult::Failed;
	}

	/*
	for (TActorIterator<APlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		APlayerCharacter* PCharacter = *ActorItr;
		if (PCharacter)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), PCharacter);

			return EBTNodeResult::Succeeded;
		}
	}*/

	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, PCharacter->GetName());
	if(PCharacter)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID(), PCharacter);
		return EBTNodeResult::Succeeded;
	}



	return EBTNodeResult::Failed;
}



