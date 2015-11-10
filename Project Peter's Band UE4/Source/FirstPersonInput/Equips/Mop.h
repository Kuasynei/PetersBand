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
	//End of the mop
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* Collider;

protected:
	UFUNCTION()
		virtual void OnActorOverlap(AActor* OtherActor);
};
