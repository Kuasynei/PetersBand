// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlap);
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
	if (isWithinTrigger == true)
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("BUTTON PRESSED INSIDE OF TRIGGER"));
		isWithinTrigger = false;
	}
	else
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("BUTTON PRESSED OUTSIDE OF TRIGGER"));

}

void APlayerCharacter::SetWithin(bool wBool)
{
	isWithinTrigger = wBool;
}

/*void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingHitPlayer"));
		
		if (OtherActor->ActorHasTag(FName(TEXT("TriggerBox"))) == true)
		{
			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("PlayerHit"));

			SetWithin(true);
		}
	}
}*/