// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "ShadowAnnaCharacter.h"
#include "ShadowAnnaController.h"

AShadowAnnaController::AShadowAnnaController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponentTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void AShadowAnnaController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AShadowAnnaCharacter* Character = Cast<AShadowAnnaCharacter>(Pawn);

	if (Character && Character->BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*Character->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Character->BehaviorTree);
	}
}

UBlackboardComponent* AShadowAnnaController::GetBlackBoardComponent()
{
	return BlackboardComponent;
}

