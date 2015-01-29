// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "sayLaVieHUD.generated.h"

/**
 * 
 */
UCLASS()
class SAYLAVIE_API AsayLaVieHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	//Setting the Font for the HUD
	UPROPERTY()
	UFont* HUDFont;

	UPROPERTY()
	FString DisplayText;

	int32 dialogueTimer;

	bool isDialogue;

	virtual void Tick(float DeltaSeconds) OVERRIDE;

	UPROPERTY()
	FString dialogue;
	
	//As the name would suggest, this is the function that draws the HUD
	virtual void DrawHUD() override;
	void Dialogue(FString);
	
};
