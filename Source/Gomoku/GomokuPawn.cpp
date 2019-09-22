// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GomokuPawn.h"

#include "DrawDebugHelpers.h"

AGomokuPawn::AGomokuPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AGomokuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AGomokuPawn::TriggerClick);
}

void AGomokuPawn::TriggerClick()
{

}