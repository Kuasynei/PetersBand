// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "UIPlayerController.h"

void AUIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		if (APlayerController::WasInputKeyJustPressed(EKeys::P))
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



