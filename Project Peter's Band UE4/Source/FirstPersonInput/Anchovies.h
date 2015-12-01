// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseAI.h"
#include "Anchovies.generated.h"

UCLASS()
class FIRSTPERSONINPUT_API AAnchovies : public ABaseAI
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnchovies();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh1;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh2;
	
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh3;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh4;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh5;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* skeleMesh6;

};
