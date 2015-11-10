// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "DoorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API UDoorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bDoorOpen;
};
