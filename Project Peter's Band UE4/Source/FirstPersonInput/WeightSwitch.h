// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "WeightSwitch.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AWeightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeightSwitch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	AInteractable *TargetToAffect;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	UFUNCTION()
	virtual void OnActorOverlap(AActor* OtherActor);

	UFUNCTION()
	virtual void OnActorOverlapEnd(AActor* OtherActor);
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Collider;

private:

	bool bIsActivated;

};
