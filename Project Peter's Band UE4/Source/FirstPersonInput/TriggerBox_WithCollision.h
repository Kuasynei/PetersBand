// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "TriggerBox_WithCollision.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ATriggerBox_WithCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerBox_WithCollision();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool GetIsWithin(bool IsWithin);

	UPROPERTY(EditAnywhere)
	APlayerCharacter* player;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collider;


	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);
};
