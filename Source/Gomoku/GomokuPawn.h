// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"

#include "GomokuPawn.generated.h"

UCLASS(config=Game)
class AGomokuPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	void TriggerClick();
};
