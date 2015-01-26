// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "minigameActor.h"
#include "minigameController.generated.h"

/**
 * 
 */
UCLASS()
class SAYLAVIE_API AminigameController : public AActor{

	GENERATED_UCLASS_BODY()
	public:
		bool isActive;
		
		TSubobjectPtr<USphereComponent> collision;

		TSubobjectPtr<UStaticMeshComponent> mesh;	

		TSubclassOf<class AminigameActor> WhatToSpawn;

		virtual void Interact(){};

		AminigameActor* Spawn(FVector);
};
