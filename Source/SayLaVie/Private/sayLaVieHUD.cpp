// Fill out your copyright notice in the Description page of Project Settings.

#include "SayLaVie.h"
#include "SayLaVieCharacter.h"
#include "sayLaVieHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"


AsayLaVieHUD::AsayLaVieHUD(const class FPostConstructInitializeProperties& PCIP) :Super(PCIP)
{

	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/Roboto"));
	HUDFont = HUDFontOb.Object;
	DisplayText = "";
	dialogue = "Hello World, this is Dialogue";
	dialogueTimer = 0;
	isDialogue = false;

}




/*
To display text simply modify the value of DisplayText

To post dialoge to the screen, simply call the dialogue function passing the
dialogue text as an FString. The string will stay on the screen for a default time
which can be modified by changing the value of dialogueTimer

*/
void AsayLaVieHUD::DrawHUD()
{
	Super::DrawHUD();





	ASayLaVieCharacter* criossant = Cast<ASayLaVieCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);
	DrawText(DisplayText, FColor::Red, 800, 800, HUDFont);
	if (criossant->printToScreen == ""){
		isDialogue = false;
	}
	else{
		isDialogue = true;
		dialogueTimer = 30;
		Dialogue(criossant->printToScreen);
	}

	if (isDialogue){
		//								Upper Left (X,Y), SizeX, SizeY
		DrawRect(FLinearColor(1, 1, 1, 1), 450.0, 520.0, 400.0, 80.0);
		DrawText(dialogue, FColor::Red, 550, 550, HUDFont);
	}

	//if (criossant->printToScreen != "")
		//AsayLaVieHUD::Dialogue(criossant->printToScreen);

}

//Pass strings of dialogue to this function for them to be printed to the screen
void AsayLaVieHUD::Dialogue(FString newDialogue){
	/*
	We may want to write a function that checks the length of the input strings,
	parses them to the correct size, and then prints them to the screen from a
	queue. Otherwise we will need to ensure that all of our input strings are
	formatted correctly
	*/

	AsayLaVieHUD::dialogue = newDialogue;
	AsayLaVieHUD::dialogueTimer = 2000;
}

void AsayLaVieHUD::Tick(float DeltaSeconds){

}