// Fill out your copyright notice in the Description page of Project Settings.

#include "SayLaVie.h"
#include "minigameActor.h"

AminigameActor::AminigameActor(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP){

	//This is the foundation for a collision mesh
	//This object still needs a mesh attached to it, this should be done in the interact function of the appropriate minigameController
	collision = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("CollisionSubComponent"));
	RootComponent = collision;
	mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TheMesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Sphere"));
	mesh->SetStaticMesh(MeshObj.Object);
	mesh->SetSimulatePhysics(false);
	mesh->AttachTo(RootComponent);

}


