// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstPersonInput.h"
#include "UIPlayerController.h"

void AUIPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		if (APlayerController::WasInputKeyJustPressed(EKeys::P))
		{
			AUIPlayerController::PauseMenu();
			SetPause(true);

		}


}

void AUIPlayerController::PauseMenu()
{

	if (UIPauseMenu)
	{
		pauseMenu = CreateWidget<UUserWidget>(this, UIPauseMenu);

		if (pauseMenu)
		{
			pauseMenu->AddToViewport(0);
			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(pauseMenu->GetCachedWidget());
			SetInputMode(Mode);



		}

		bShowMouseCursor = true;

	}


}



