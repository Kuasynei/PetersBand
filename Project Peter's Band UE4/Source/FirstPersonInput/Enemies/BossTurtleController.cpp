/* Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BossTurtleController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BossTurtleCharacter.h"

ABossTurtleController::ABossTurtleController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ABossTurtleController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	ABossTurtleCharacter* Character = Cast<ABossTurtleCharacter>(Pawn);
	if (Character && Character->BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*Character->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Character->BehaviorTree);


	}
}

UBlackboardComponent* ABossTurtleController::GetBlackBoardComponent()
{
	return BlackboardComponent;
}

void ABossTurtleController::RedirectToCharacter(AActor* OtherActor)
{
	ABossTurtleCharacter* Character = Cast<ABossTurtleCharacter>(OtherActor);
	Character->NextWayPoint();
}

*/