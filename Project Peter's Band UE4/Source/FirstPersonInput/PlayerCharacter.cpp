// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "TriggerBox_WithCollision.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	BaseTurnRate = 60.f;
	BaseLookUpRate = 60.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	//BOX PICKUP CODE//
	Hand = CreateDefaultSubobject<USceneComponent>(TEXT("Hand"));
	Hand->AttachTo(RootComponent);
	Hand->RelativeLocation = FVector(100, 0, 0);
	holdingObject = false;
	//BOX PICKUP CODE//

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
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

//MOVEMENT CODE//

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); //yaw = horizontal rotation
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); //pitch vertical rotation
}

//MOVEMENT CODE END//


//USE BUTTON CODE//

void APlayerCharacter::ActivateButton()
{
	
	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, ATriggerBox_WithCollision::StaticClass());

	if (Hand->AttachChildren.Num() > 0)
	{
		USceneComponent *AttachedObject;

		AttachedObject = Hand->AttachChildren[0];

		AttachedObject->DetachFromParent();

		//Cast<ATriggerBox_WithCollision>(AttachedObject)->OnDropped();

		AttachedObject->SetWorldLocation(Hand->GetComponentLocation());

		Cast<ATriggerBox_WithCollision>(OverlappingActors[0])->OnDropped();

		//holdingObject = false;

		//@Note: Hack for a one floor setup.
		//AttachedObject->SetWorldLocation(FVector(Hand->GetComponentLocation().X, Hand->GetComponentLocation().Y, 50));
	}
	else
	{
		if (OverlappingActors.Num() > 0)
		{
			AActor *OtherActor = OverlappingActors[0];

			if (OtherActor->ActorHasTag(TEXT("Door")))
			{
				Cast<ATriggerBox_WithCollision>(OtherActor)->OpenDoor();
			}
			if (Cast<ATriggerBox_WithCollision>(OtherActor)->isLiftable())
			{
				//if (this->GetActorLocation().Y < OtherActor->GetActorLocation().Y)
				{
					Cast<ATriggerBox_WithCollision>(OtherActor)->OnPickedUp();
					OtherActor->AttachRootComponentTo(Hand, NAME_None, EAttachLocation::SnapToTarget);
				}
			}
		}
	}


}

//USE BUTTON CODE END//

void APlayerCharacter::SetWithin(bool wBool)
{
	isWithinTrigger = wBool;
}

void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingHitPlayer"));
		
		if (OtherActor->ActorHasTag(FName(TEXT("TriggerBox"))) == true)
		{
			SetWithin(true);

			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("PlayerHit"));

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
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, TEXT("SomethingHitPlayer"));

		if (OtherActor->ActorHasTag(FName(TEXT("TriggerBox"))) == true)
		{
			SetWithin(false);
		}
	}
}