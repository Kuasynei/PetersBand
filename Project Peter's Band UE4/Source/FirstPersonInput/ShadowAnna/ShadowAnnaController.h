// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShadowAnnaController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API AShadowAnnaController : public AAIController
{
	GENERATED_BODY()

public: 
	AShadowAnnaController();

	UBlackboardComponent* GetBlackBoardComponent();

	virtual void Possess(APawn* Pawn) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BlackboardComponent;
	
	
	
	
};
