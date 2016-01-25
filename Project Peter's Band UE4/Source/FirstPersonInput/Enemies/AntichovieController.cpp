// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AntichovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AntichovieCharacter.h"

AAntichovieController::AAntichovieController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAntichovieController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AAntichovieCharacter* Character = Cast<AAntichovieCharacter>(Pawn);
	if (Character && Character->BehaviorTree)
	{
		BlackboardComponent->InitializeBlackboard(*Character->BehaviorTree->BlackboardAsset);
		BehaviorTreeComponent->StartTree(*Character->BehaviorTree);


	}
}

UBlackboardComponent* AAntichovieController::GetBlackBoardComponent()
{
	return BlackboardComponent;
}

void AAntichovieController::RedirectToCharacter(AActor* OtherActor)
{
	AAntichovieCharacter* Character = Cast<AAntichovieCharacter>(OtherActor);
	Character->NextWayPoint();
}