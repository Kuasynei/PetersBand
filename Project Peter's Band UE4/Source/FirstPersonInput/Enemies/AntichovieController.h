// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AntichovieController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API AAntichovieController : public AAIController
{
	GENERATED_BODY()

public:
	AAntichovieController();
	virtual void Possess(APawn* Pawn) override;

	UBlackboardComponent* GetBlackBoardComponent();

	UFUNCTION()
		void RedirectToCharacter(AActor* OtherActor);

protected:
	UPROPERTY(VisibleAnywhere)
		UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere)
		UBlackboardComponent* BlackboardComponent;

};

