// Fill out your copyright notice in the Description page of Project Settings.

#include "SayLaVie.h"
#include "minigameController.h"
#include "groceryMinigame.h"
#include "sayLaVieHUD.h"
#include "SayLaVieCharacter.h"
#include <iostream>
#include <string>
#include <random>
#include <cstdlib>

/*
There are a handful of unncecessary includes here, none of them are
gamebreaking, but it is an inefficiency. They have all been used at one
point or another, and several are still being used. However, this should
be sorted out eventually
*/

AgroceryMinigame::AgroceryMinigame(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP){

	PrimaryActorTick.bCanEverTick = true;

	interactionTimer = 0;

	collision = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionSubcomponent"));
	RootComponent = collision;
	mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TheMesh"));
	mesh->SetSimulatePhysics(true);
	mesh->AttachTo(RootComponent);
	//static ConstructorHelpers::FObjectFinder Shape_TriPyramid(TEXT("StaticMesh'/Game/StarterContent/Shapes'"));
	//mesh->SetStaticMesh(Shape_TriPyramid);
	//This is where we should attach a model to this minigameController
	isActive = true;
	temp[0] = "Bonjour";
	temp[1] = "Salut";
	temp[2] = "Parle vour francais";
	temp[3] = "Consulter un robot";
	temp[4] = "Fetchez la vache";
	temp[5] = "Oui oui baguette croissant";

}

//Inherited from minigameController, write code for it here
void AgroceryMinigame::Interact(){
	Super::Interact();
	ASayLaVieCharacter* criossant = Cast<ASayLaVieCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	criossant->printToScreen = "Interact Successful";
	AgroceryMinigame::talk();
	//We need to set spawn "parameters" for minigameActors that will be spawned
	//also this is where we should call the spawn function from

	//NOTE: This function is called from the SayLaVieCharacter.cpp function also titled Interact
	//when the player presses the "E" key and is within a certain distance
}

/*
This funtion is still very much under development

It currently prints to the screen a random reply from an array
*/
void AgroceryMinigame::talk(){
	//I'm still using the player character as a means of passing information until I get the hang of the the GetWorld function
	//so this piece of code is just here to pass the string to the HUD
	ASayLaVieCharacter* criossant = Cast<ASayLaVieCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	criossant->printToScreen = temp[rand() % 6];

	isActive = false;
	//32 = one second
	interactionTimer += 96;
}


//This function is inherited from AActor. It is called every second
void AgroceryMinigame::Tick(float DeltaTime){
	if (interactionTimer > 0){
		interactionTimer--;
		if (interactionTimer == 0){
			isActive = true;
			ASayLaVieCharacter* criossant = Cast<ASayLaVieCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
			criossant->printToScreen = "";
		}
	}
}