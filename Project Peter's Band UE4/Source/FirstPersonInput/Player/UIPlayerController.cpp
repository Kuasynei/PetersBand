// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "UIPlayerController.h"

void AUIPlayerController::BeginPlay()
{
	if (!GetWorld()->GetMapName().Contains("MainMenu"))
	{
		bShowMouseCursor = false;
	}
}

void AUIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->GetMapName().Contains("MainMenu"))
	{
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Red, GetWorld()->GetMapName());
	}
	else
	{
		if (APlayerController::WasInputKeyJustPressed(EKeys::P) || APlayerController::WasInputKeyJustPressed(EKeys::Escape))
		{
			if (!paused)
			{
				AUIPlayerController::PauseMenu();
				SetPause(true);
				paused = true;
			}

			else if (paused)
			{
				AUIPlayerController::PauseMenu();
				SetPause(false);
				paused = false;
			}

		}
	}
}

void AUIPlayerController::BlueprintPauseMenu()
{
	if (!paused)
	{
		AUIPlayerController::PauseMenu();
		SetPause(true);
		paused = true;
	}

	else if (paused)
	{
		AUIPlayerController::PauseMenu();
		SetPause(false);
		paused = false;
	}
}

void AUIPlayerController::PauseMenu()
{

	if (!paused)
	{
		if (UIPauseMenu)
		{
			pauseMenu = CreateWidget<UUserWidget>(this, UIPauseMenu);

			if (pauseMenu)
			{
				pauseMenu->AddToViewport(0);
				//FInputModeUIOnly Mode;
				//Mode.SetWidgetToFocus(pauseMenu->GetCachedWidget());
				//SetInputMode(Mode);



			}

			bShowMouseCursor = true;

		}
	}

	else if (paused)
	{
		pauseMenu->RemoveFromViewport();
		bShowMouseCursor = false;
	
	}


}



