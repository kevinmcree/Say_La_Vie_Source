// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SayLaVie.h"
#include "sayLaVieHUD.h"
#include "SayLaVieGameMode.h"
#include "SayLaVieCharacter.h"

ASayLaVieGameMode::ASayLaVieGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	HUDClass = AsayLaVieHUD::StaticClass();
}
