// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ChoiceCheck.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AChoiceCheck : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool RealityChoice;
	
public:	
	// Sets default values for this actor's properties
	AChoiceCheck();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UFUNCTION()
		virtual void OnActorOverlap(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collider;
};
