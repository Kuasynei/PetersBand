/* Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "BossTurtleCharacter.h"
#include "BossTurtleController.h"



// Sets default values
ABossTurtleCharacter::ABossTurtleCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = ABossTurtleCharacter::StaticClass();

	WaypointAt = 0;
	LightOn = false;

	ABossTurtleController* Controller;
	Controller = Cast<ABossTurtleController>(this->GetController());

	OnActorBeginOverlap.AddDynamic(this, &ABossTurtleCharacter::OnActorOverlaping);

}


void ABossTurtleCharacter::OnActorOverlaping(AActor* OtherActor)
{
	if (OtherActor != GetOwner())
	{
		if (OtherActor->GetName().Contains("Light"))
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

void ABossTurtleCharacter::NextWayPoint()
{

	ABossTurtleController* Controller;

	Controller = Cast<ABossTurtleController>(this->GetController());
	if (!LightOn)
	{
		if (PathA.Num() > 1)
		{
			if (PathA.Last() == PathA[WaypointAt])
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
				WaypointAt = (PathA.Num() - 1);
			}
			else
			{
				WaypointAt -= 1;
			}
		}
		if (Controller != nullptr)
		{
			Controller->GetBlackBoardComponent()->SetValue<UBlackboardKeyType_Vector>(DestinationKeyName, PathA[WaypointAt]->GetActorLocation());
		}
	}
}

*/