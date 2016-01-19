// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UIPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class FIRSTPERSONINPUT_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
			TSubclassOf<UUserWidget> UIPauseMenu;
		
		UFUNCTION(BlueprintCallable, Category = "PauseMenu")
			void BlueprintPauseMenu();


protected:

	UUserWidget* pauseMenu;
	
	void PauseMenu();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	bool paused = false;

};
