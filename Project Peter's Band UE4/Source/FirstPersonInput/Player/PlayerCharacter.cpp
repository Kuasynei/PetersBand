// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Interactables/Interactable.h"
#include "PlayerCharacter.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 90.f);

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
	Hand->AttachTo(FirstPersonCameraComponent);
	Hand->RelativeLocation = FVector(100, 0, 0);
	//BOX PICKUP CODE//

	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlayerCharacter::OnActorOverlapEnd);
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bCurrentlyLiftingBox = false;

}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isWalkingForward || isWalkingRight)
	{
		if (CanJump())
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), WalkSound, GetActorLocation());
	}
	if (isJumpingGruntCheck)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), GruntSound, GetActorLocation());
		isJumpingGruntCheck = false;
	}

	if (GetVelocity().Z == 0 && isJumpingGroundCheck)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), JumpSound, GetActorLocation());
		isJumpingGroundCheck = false;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("UseButton", IE_Pressed, this, &APlayerCharacter::ActivateButton);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Depending on the key pressed, will change the player's equip.
	InputComponent->BindAction("EquipSlot1", IE_Pressed, this, &APlayerCharacter::EquipSlot1);
	InputComponent->BindAction("EquipSlot2", IE_Pressed, this, &APlayerCharacter::EquipSlot2);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
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
void APlayerCharacter::StartJump()
{
	if (GetVelocity().Z == 0)
	{
		isJumpingGruntCheck = true;
		isJumpingGroundCheck = true;
		Jump();
	}
}


//MOVEMENT CODE//
void APlayerCharacter::MoveForward(float Value)
{
	
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		isWalkingForward = true;
	}
	else
		isWalkingForward = false;
	
}

void APlayerCharacter::MoveRight(float Value)
{
	
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
		isWalkingRight = true;
	}
	else
		isWalkingRight = false;
	
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
	//If the player is lifting a box and the button is pressed then all we should do is drop the box.
	if (bCurrentlyLiftingBox)
	{
		bCurrentlyLiftingBox = false;

		PickedUpBox->Drop(this);

		return;
	}

	//Create an array to hold all of the overlapping actors on the player
	TArray<AActor*> OverlappingActors;

	GetOverlappingActors(OverlappingActors, AInteractable::StaticClass());

	//Create an interactable pointer to hold the closest object at the end of it as well as a float to hold the closest distance
	AInteractable *ClosestObject = nullptr;

	//@note: FLT_MAX just sets the float to be the higest number possible for a float
	float ClosestObjectDist = FLT_MAX;

	//Loop that checks every object in the array to find what the closest object is
	for (int i = 0; i < OverlappingActors.Num(); i++)
	{
		float ObjectDistance = FVector::Dist(this->GetActorLocation(), OverlappingActors[i]->GetActorLocation());

		if (ObjectDistance < ClosestObjectDist)
		{
			ClosestObjectDist = ObjectDistance;
			ClosestObject = Cast<AInteractable>(OverlappingActors[i]);
		}
	}

	//As long as the closest actor is not null then it runs the interact function on that object
	if (ClosestObject != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, ClosestObject->GetName());
		if (ClosestObject->GetName().Contains("Door"))
		{
			if (ClosestObject->GetName().Contains("Interactable"))
			{
				ClosestObject->Interact(this);
			}
		}
		else
		{
			ClosestObject->Interact(this);
		}
	}
}
//USE BUTTON CODE END//


USceneComponent* APlayerCharacter::GetHand()
{
	//Returns the hand object that the mop and liftable objects attach to
	return Hand;
}


void APlayerCharacter::EquipSlot1() //Nothing Equipped
{
	EquippedIndex = 1;
	Unequip();
}
void APlayerCharacter::EquipSlot2() //First Equip
{
	if (UnlockedEquips >= 1)
	{
		EquippedIndex = 2;
		Equip(Equips[0]);
	}
}


void APlayerCharacter::Equip(TSubclassOf<ABaseEquips> EquipType)
{
	if (Equipped != NULL)
	{
		Unequip();
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	Equipped = GetWorld()->SpawnActor<ABaseEquips>(EquipType, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	Equipped->AttachRootComponentTo(GetMesh(), "BN_RPalm_01");
}

void APlayerCharacter::Unequip()
{
	if (Equipped != NULL)
	{
		Equipped->Destroy();
		Equipped = NULL;
	}
}

//Sets the players currently lifted object
void APlayerCharacter::SetObjectLifted(ALiftableBox* Box)
{
	PickedUpBox = Box;
	bCurrentlyLiftingBox = true;
}

void APlayerCharacter::SetLastChoice(bool ChoiceMade)
{
	LastChoiceMade = ChoiceMade;
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Black, TEXT("DING"));
}

bool APlayerCharacter::GetLastChoice()
{
	return LastChoiceMade;
}


void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetName().Contains("Fantasy"))
		{
			if (FantasyCounter == NULL)
			{
				FantasyCounter = 0;
			}
			if (FantasyCounter != NULL)
			{
				UpdateCamera(FantasyCounter);
			}
		}
	}
}


void APlayerCharacter::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//
	}
}

void APlayerCharacter::UpdateCamera(float Counter)
{
	TheCameraToEffect = Cast<ACameraActor>(this->GetFirstPersonCameraComponent());

	if (Counter == 0)
	{
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.FilmSaturation = 1;
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.VignetteIntensity = 0;
	}
	else if (Counter == 1)
	{
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.FilmSaturation = 1.2;
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.VignetteIntensity = 0.1;
	}
	else if (Counter == 2)
	{
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.FilmSaturation = 1.35;
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.VignetteIntensity = 0.2;
	}
	else if (Counter > 2)
	{
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.FilmSaturation = 1.5;
		TheCameraToEffect->GetCameraComponent()->PostProcessSettings.VignetteIntensity = 0.3;
	}
}

