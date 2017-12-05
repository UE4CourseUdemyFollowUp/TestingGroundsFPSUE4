// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestingGroundsFPSUE4HUD.generated.h"

UCLASS()
class ATestingGroundsFPSUE4HUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestingGroundsFPSUE4HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

