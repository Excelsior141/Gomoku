// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "GomokuPawn.h"


AGomokuPawn::AGomokuPawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
	, lastHitCell(nullptr)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AGomokuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Released, this, &AGomokuPawn::TriggerClick);
}

void AGomokuPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		FVector Start;
		FVector Dir;
		FVector End;

		PlayerController->DeprojectMousePositionToWorld(Start, Dir);
		End = Start + (Dir * 8000.0f);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

		if (HitResult.Actor.IsValid() && HitResult.Actor->GetClass() == AGomokuBoardCell::StaticClass())
		{
			AGomokuBoardCell* HitCell = Cast<AGomokuBoardCell>(HitResult.Actor.Get());

			if (HitCell == nullptr || HitCell->GetState() != AGomokuBoardCell::State::Disabled)
			{
				return;
			}

			if (lastHitCell != HitCell)
			{
				if (lastHitCell != nullptr)
				{
					lastHitCell->SetState(AGomokuBoardCell::State::Disabled);
				}
				
				HitCell->SetState(AGomokuBoardCell::State::Highlighted);
				lastHitCell = HitCell;
			}
		}
		else if (lastHitCell != nullptr)
		{
			lastHitCell->SetState(AGomokuBoardCell::State::Disabled);
			lastHitCell = nullptr;
		}
	}
}

void AGomokuPawn::TriggerClick()
{
	if (lastHitCell != nullptr)
	{
		lastHitCell->SetState(AGomokuBoardCell::State::Player);
		lastHitCell = nullptr;
	}
}