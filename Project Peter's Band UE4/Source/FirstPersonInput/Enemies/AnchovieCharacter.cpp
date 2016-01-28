// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "AnchovieCharacter.h"
#include "AnchovieController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


// Sets default values
AAnchovieCharacter::AAnchovieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AAnchovieController::StaticClass();

	WaypointAt = 0;
	LightOn = false;

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

	AAnchovieController* Controller;
	Controller = Cast<AAnchovieController>(this->GetController());

	OnActorBeginOverlap.AddDynamic(this, &AAnchovieCharacter::OnActorOverlaping);

}


void AAnchovieCharacter::OnActorOverlaping(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetName().Contains("Lever"))
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
		else if (OtherActor->GetName().Contains("Light"))
		{
			TheSwitch = Cast<ALightSwitch>(OtherActor);

			if (TheSwitch != NULL)
			{
				if (TheSwitch->GetIsOn() == true)
				{
					if (LightOn == false)
					{
						LightOn = true;
					}
					else
					{
						LightOn = false;
					}
				}
			}
		}
	}
}

void AAnchovieCharacter::NextWayPoint()
{

	AAnchovieController* Controller;

	Controller = Cast<AAnchovieController>(this->GetController());
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
			if (WaypointAt == 0)
			{
				WaypointAt = (Waypoints.Num() - 1);
			}
			else
			{
				WaypointAt -= 1;
			}
		}
		if (Controller != nullptr)
		{
			Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(DestinationKeyName, Waypoints[WaypointAt]->GetActorLocation());
		}
	}
}

