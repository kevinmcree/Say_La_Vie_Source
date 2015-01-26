// Fill out your copyright notice in the Description page of Project Settings.

#include "SayLaVie.h"
#include "minigameActor.h"

AminigameActor::AminigameActor(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP){

	//This is the foundation for a collision mesh
	//This object still needs a mesh attached to it, this should be done in the interact function of the appropriate minigameController
	collision = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionSubcomponent"));
	RootComponent = collision;
	mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TheMesh"));
	mesh->SetSimulatePhysics(true);
	mesh->AttachTo(RootComponent);

}


