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
	//Root Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* RootCollider;

	//The end of the mop
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* MopHitbox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USkeletalMeshComponent* MopMesh;


protected:
	UFUNCTION()
		virtual void OnActorOverlap(AActor* OtherActor);
};
