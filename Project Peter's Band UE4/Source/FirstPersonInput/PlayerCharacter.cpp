// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TriggerBox_WithCollision.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Hand = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));

	Hand->AttachTo(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlapEnd);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("UseButton", IE_Pressed, this, &APlayerCharacter::ActivateButton);

}

void APlayerCharacter::ActivateButton()
{
	if (Hand->AttachChildren.Num() > 0)
	{
		USceneComponent *AttachedObject;

		AttachedObject = Hand->AttachChildren[0];

		AttachedObject->DetachFromParent();

		AttachedObject->SetWorldLocation(Hand->GetComponentLocation());

		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("Blah"));

	}
	else
	{
		TArray<AActor*> OverlappingActors;

		GetOverlappingActors(OverlappingActors, ATriggerBox_WithCollision::StaticClass());

		if (OverlappingActors.Num() > 0)
		{
			AActor *OtherActor = OverlappingActors[0];
			OtherActor->AttachRootComponentTo(Hand, NAME_None, EAttachLocation::SnapToTarget);
		}
	}
		

}

void APlayerCharacter::SetWithin(bool wBool)
{
	isWithinTrigger = wBool;
}

void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingHitPlayer"));
		
		if (OtherActor->ActorHasTag(FName(TEXT("TriggerBox"))) == true)
		{
			SetWithin(true);

			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("PlayerHit"));

			/*if (Cast<ATriggerBox_WithCollision>(OtherActor) == nullptr)
			{
				GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("OtherActor Cast Was Null"));
			}
			else if (Cast<ATriggerBox_WithCollision>(OtherActor)->canBeLifted == true && isEPressed == true)
			{
			}*/
		}
	}
}

void APlayerCharacter::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingHitPlayer"));

		if (OtherActor->ActorHasTag(FName(TEXT("TriggerBox"))) == true)
		{
			SetWithin(false);
		}
	}
}