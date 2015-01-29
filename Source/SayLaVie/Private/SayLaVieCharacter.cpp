// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "SayLaVie.h"
#include "sayLaVieHUD.h"
#include "groceryMinigame.h"
#include "SayLaVieCharacter.h"

//////////////////////////////////////////////////////////////////////////
// ASayLaVieCharacter

ASayLaVieCharacter::ASayLaVieCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	printToScreen = "";

	//This is the player component that allows the player to interact with in game objects
	InteractionRadius = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("InteractionRadius"));
	InteractionRadius->AttachTo(RootComponent);
	InteractionRadius->SetSphereRadius(200.f);

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	CharacterMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	CharacterMovement->JumpZVelocity = 600.f;
	CharacterMovement->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASayLaVieCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ASayLaVieCharacter::playerInteract);


	InputComponent->BindAxis("MoveForward", this, &ASayLaVieCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASayLaVieCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ASayLaVieCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ASayLaVieCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &ASayLaVieCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &ASayLaVieCharacter::TouchStopped);
}

void ASayLaVieCharacter::playerInteract(){

	//Creates an array of actors within the players sphere of interaction
	TArray<AActor*> OverlappingActors;
	printToScreen = "Interacting";
	//AsayLaVieHUD* TheHUD = (AsayLaVieHUD*)GetWorld()->GetFirstLocalPlayerFromController()->MyHUD;
	InteractionRadius->GetOverlappingActors(OverlappingActors);

	//Iterates through the possible actors with which the player is currently colliding
	for (int i = 0; i < OverlappingActors.Num(); i++){
		/*
		We may need to write a tie breaker algorithm to determine the object with which the player
		is most likely trying to interact with
		*/
		/*
		Detect Class type
		Cast to appropriate Actor type
		Call appropriate actor method
		EX Characters will cause dialogue to appear on screen
		*/

		//Apparently casting in this fashion rather than the traditional fashion avoids fatal game crashes
		/*
		There is currently a bug in the following lines of code where the object is never successfully cast...
		I'm tired right now and so I'll come back to this later. If you are seeing this then I haven't gotten around to it
		because other classes got crazy. However, this is my top priority for 170 at the moment, so it will get fixed soon.
		*/
		AgroceryMinigame* minigame = Cast<AgroceryMinigame>(OverlappingActors[i]);
		//AgroceryMinigame* minigame = (AgroceryMinigame*)(CollidingCharacters[i]);
		printToScreen = "Attempting to Capture Actors";

		if (minigame && minigame->isActive){
			printToScreen = "Actor Capture Successful";
			//minigame->isActive = false;
			minigame->Interact();
		}
		else if (minigame && !minigame->isActive)
			printToScreen = "Inactive";
		else{
			printToScreen = "Cast Failed";
		}
	}
}


void ASayLaVieCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	printToScreen = "Jumping";

	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void ASayLaVieCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void ASayLaVieCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASayLaVieCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASayLaVieCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASayLaVieCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
