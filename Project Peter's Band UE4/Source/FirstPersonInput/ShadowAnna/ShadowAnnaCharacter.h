// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "ShadowAnnaCharacter.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AShadowAnnaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShadowAnnaCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly)
	FName DestinationKeyName;

	UPROPERTY(EditAnywhere)
	ATargetPoint* Destination;
	
	
};
