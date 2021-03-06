// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "Interactable.h"
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


	if (DefaultEquipClass)
	{
		Equip(DefaultEquipClass);
	}
	

	bCurrentlyLiftingBox = false;

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

	if (ClosestObject != nullptr)
	{
		ClosestObject->Interact(this);

	}
}

//USE BUTTON CODE END//


USceneComponent* APlayerCharacter::GetHand()
{
	return Hand;
}

void APlayerCharacter::Equip(TSubclassOf<ABaseEquips> EquipType)
{
	if (Equipped != NULL && Equipped->IsA(EquipType))
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;

	Equipped = GetWorld()->SpawnActor<ABaseEquips>(EquipType, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParameters);
	Equipped->AttachRootComponentTo(RootComponent);
	//Equipped->AttachRootComponentTo(GetMesh(), TEXT("RightHand"));
}

void APlayerCharacter::SetObjectLifted(ALiftableBox* Box)
{
	PickedUpBox = Box;
	bCurrentlyLiftingBox = true;
}

void APlayerCharacter::OnActorOverlap(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
	}
}

void APlayerCharacter::OnActorOverlapEnd(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		//
	}
}
