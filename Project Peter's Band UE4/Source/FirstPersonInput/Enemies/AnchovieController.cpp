// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnchovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AnchovieCharacter.h"

AAnchovieController::AAnchovieController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAnchovieController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AAnchovieCharacter* Character = Cast<AAnchovieCharacter>(Pawn);
	if (Character && Character->BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*Character->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Character->BehaviorTree);


	}
}

UBlackboardComponent* AAnchovieController::GetBlackBoardComponent()
{
	return BlackboardComponent;
}

void AAnchovieController::SegwayTest(AActor* OtherActor)
{
	AAnchovieCharacter* Character = Cast<AAnchovieCharacter>(OtherActor);
	Character->NextWayPoint();
}