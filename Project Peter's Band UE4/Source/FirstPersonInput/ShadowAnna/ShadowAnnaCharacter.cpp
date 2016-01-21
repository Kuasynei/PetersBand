// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "ShadowAnnaController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "ShadowAnnaCharacter.h"


// Sets default values
AShadowAnnaCharacter::AShadowAnnaCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AShadowAnnaController::StaticClass();

}

// Called when the game starts or when spawned
void AShadowAnnaCharacter::BeginPlay()
{
	Super::BeginPlay();

	AShadowAnnaController* Controller;

	Controller = Cast<AShadowAnnaController>(this->GetController());
	if (Controller != nullptr)
	{
		Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(DestinationKeyName, Destination->GetActorLocation());
	}

	
}

