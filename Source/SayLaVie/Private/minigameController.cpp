// Fill out your copyright notice in the Description page of Project Settings.

#include "SayLaVie.h"
#include "minigameActor.h"
#include "minigameController.h"

AminigameController::AminigameController(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP){

	//This is not currently in use, but it seems useful in the future
	isActive = false;

	//This is the foundation for attaching a collision mesh to an object
	collision = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionSubcomponent"));
	RootComponent = collision;
	mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TheMesh"));
	mesh->SetSimulatePhysics(true);
	mesh->AttachTo(RootComponent);

}

/*
This is the spawn method inherited by all of the minigame classes
if the spawning is successful it returns a pointer to the object that has been spawned
*/
AminigameActor* AminigameController::Spawn(FVector location){
	UWorld* const World = GetWorld();
	if (World){
		FActorSpawnParameters params;
		params.Owner = this;
		params.Instigator = Instigator;

		//This is the rotation that the actor will spawn at
		FRotator rotation;
		rotation.Yaw = 0;
		rotation.Pitch = 0;
		rotation.Roll = 0;

		return World->SpawnActor<AminigameActor>(WhatToSpawn, location, rotation, params);
	}
	else return nullptr;
}
