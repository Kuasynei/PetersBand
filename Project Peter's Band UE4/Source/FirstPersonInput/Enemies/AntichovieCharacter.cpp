// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AntichovieCharacter.h"
#include "AntichovieController.h"
#include "Interactables/Interactable.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Interactables/Lever.h"
#include "GameFramework/Actor.h"


// Sets default values
AAntichovieCharacter::AAntichovieCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAntichovieController::StaticClass();

	WaypointAt = 0;
	LightOn = false;

	WaypointsAreTheSame = false;

	skeleMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh1"));
	skeleMesh2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh2"));
	skeleMesh3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh3"));
	skeleMesh4 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh4"));
	skeleMesh5 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh5"));
	skeleMesh6 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeleMesh6"));

	skeleMesh1->AttachTo(RootComponent);
	skeleMesh2->AttachTo(RootComponent);
	skeleMesh3->AttachTo(RootComponent);
	skeleMesh4->AttachTo(RootComponent);
	skeleMesh5->AttachTo(RootComponent);
	skeleMesh6->AttachTo(RootComponent);

	AAntichovieController* Controller;
	Controller = Cast<AAntichovieController>(this->GetController());

	OnActorBeginOverlap.AddDynamic(this, &AAntichovieCharacter::OnActorOverlaping);

}


void AAntichovieCharacter::OnActorOverlaping(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		LeverToCollideWith = Cast<ALever>(OtherActor);

		if (LeverToCollideWith != NULL)
		{
			if (LeverToCollideWith->GetIsActivated() == true)
			{
				LeverToCollideWith->Interact(this);
			}
		}

	}
}

void AAntichovieCharacter::NextWayPoint()
{

	AAntichovieController* Controller;

	Controller = Cast<AAntichovieController>(this->GetController());
	if (Waypoints.Num() > 1)
	{
		if (!LightOn)
		{
			if (Waypoints.Last() == Waypoints[WaypointAt])
			{
				WaypointAt = 0;
			}
			else
			{
				WaypointAt += 1;
			}
		}
		else
		{
			if (WaypointsBlockedByLight.Num() > 0)
			{
				if (!WaypointsBlockedByLight.Find(Waypoints[WaypointAt]))
				{
					while (WaypointsAreTheSame == false)
					{
						if (!WaypointsBlockedByLight.Find(Waypoints[WaypointAt]))
						{
							if (Waypoints.Last() == Waypoints[WaypointAt])
							{
								WaypointAt = 0;
							}
							WaypointAt++;
							WaypointsAreTheSame = true;
						}
					}
				}
				else if (WaypointsBlockedByLight.Find(Waypoints[WaypointAt]))
				{
					while (WaypointsAreTheSame == false)
					{
						if (WaypointsBlockedByLight.Find(Waypoints[WaypointAt]))
						{
							if (Waypoints.Last() == Waypoints[WaypointAt])
							{
								WaypointAt = 0;
							}
							WaypointAt++;
							WaypointsAreTheSame = true;
						}
					}
				}
				WaypointsAreTheSame = false;
			}

		}
		if (Controller != nullptr)
		{
			Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(DestinationKeyName, Waypoints[WaypointAt]->GetActorLocation());
		}
	}
}

