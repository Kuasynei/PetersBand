// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ShadowAnna/ShadowAnnaController.h"
#include "DistanceCheck.h"

void UDistanceCheck::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* Blackboard = Blackboard = OwnerComp.GetBlackboardComponent();

	uint8 TargetKeyID = Blackboard->GetKeyID(TargetName);

	UObject* TargetObject = Blackboard->GetValue<UBlackboardKeyType_Object>(TargetKeyID);

	AActor* TargetActor = Cast<AActor>(TargetObject);

	AShadowAnnaController* AiController = Cast<AShadowAnnaController>(Blackboard->GetOwner());

	if (AiController && TargetActor)
	{
		Dist = FVector::Dist(TargetActor->GetActorLocation(), AiController->GetPawn()->GetActorLocation());

		Blackboard->SetValue<UBlackboardKeyType_Float>(KeyName, Dist);
	}
}


