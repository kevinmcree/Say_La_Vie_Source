// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "minigameActor.generated.h"

/**
 * 
 */
UCLASS()
class SAYLAVIE_API AminigameActor : public AActor
{
	GENERATED_UCLASS_BODY()
	
	TSubobjectPtr<USphereComponent> collision;

	TSubobjectPtr<UStaticMeshComponent> mesh;
	
	
	
};
