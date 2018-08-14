// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TestingGroundsFPSUE4GameMode.h"
#include "TestingGroundsFPSUE4HUD.h"
#include "FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGroundsFPSUE4GameMode::ATestingGroundsFPSUE4GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behavior/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundsFPSUE4HUD::StaticClass();
}
