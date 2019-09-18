// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuGameModeBase.h"
#include "GomokuPlayerController.h"
#include "GomokuPawn.h"

AGomokuGameModeBase::AGomokuGameModeBase()
{
	DefaultPawnClass = AGomokuPawn::StaticClass();
	PlayerControllerClass = AGomokuPlayerController::StaticClass();
}
