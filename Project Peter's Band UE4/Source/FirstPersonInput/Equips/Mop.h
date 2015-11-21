// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equips/BaseEquips.h"
#include "Mop.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AMop : public ABaseEquips
{
	GENERATED_BODY()

public:
	AMop();
	
	virtual void Tick(float DeltaSeconds) override;

protected:
	//The mop's hitbox
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* MopHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* MopMesh;


protected:
	UFUNCTION()
		virtual void OnActorBeginOverlap(AActor* OtherActor);

	UFUNCTION()
		virtual void OnActorEndOverlap(AActor* OtherActor);
};
