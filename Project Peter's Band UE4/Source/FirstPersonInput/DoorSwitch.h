// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DoorSwitch.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API ADoorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorSwitch();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
		AActor *ToActivate;

	UFUNCTION()
		void ActivateDoor();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent *Collider;

	UFUNCTION()
		virtual void OnActorOverlap(AActor* OtherActor);

	UFUNCTION()
		virtual void OnActorOverlapEnd(AActor* OtherActor);

	bool activated;
	
};
