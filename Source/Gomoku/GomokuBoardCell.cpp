// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuBoardCell.h"

#include "GomokuBoard.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AGomokuBoardCell::AGomokuBoardCell()
	: currentState(State::Disabled)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	dummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy"));
	RootComponent = dummyRoot;

	tokenMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/Materials/TokenMaterial.TokenMaterial")).Get();
	tokenMaterialPlayer = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("/Game/Materials/TokenMaterialPlayer.TokenMaterialPlayer")).Get();
	tokenMaterialComputer = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("/Game/Materials/TokenMaterialComputer.TokenMaterialComputer")).Get();
	
	gridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gridMesh"));
	gridMesh->SetStaticMesh(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/Shapes/Cell.Cell")).Get());
	gridMesh->SetMaterial(0, ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/Materials/CellMaterial.CellMaterial")).Get());
	gridMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	gridMesh->SetupAttachment(dummyRoot);

	tokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("tokenMesh"));
	tokenMesh->SetStaticMesh(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/Shapes/Token.Token")).Get());
	tokenMesh->SetMaterial(0, tokenMaterial);
	tokenMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
	tokenMesh->SetupAttachment(dummyRoot);
	tokenMesh->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AGomokuBoardCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGomokuBoardCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGomokuBoardCell::SetScale(float scale)
{
	gridMesh->SetWorldScale3D(FVector(scale, scale, scale));
	tokenMesh->SetWorldScale3D(FVector(scale, scale, scale));
}

void AGomokuBoardCell::SetState(AGomokuBoardCell::State state)
{
	currentState = state;

	switch (state)
	{
		case State::Disabled:
		{
			tokenMesh->SetHiddenInGame(true);
			tokenMesh->SetMaterial(0, tokenMaterial);
		} break;
		case State::Highlighted:
		{
			tokenMesh->SetHiddenInGame(false);
			tokenMesh->SetMaterial(0, tokenMaterial);
		} break;
		case State::Player:
		{
			tokenMesh->SetHiddenInGame(false);
			tokenMesh->SetMaterial(0, tokenMaterialPlayer);

			if (ParentBoard != nullptr)
			{
				ParentBoard->OnPlayerActivatedCell(X, Y);
			}
		} break;
		case State::Computer:
		{
			tokenMesh->SetHiddenInGame(false);
			tokenMesh->SetMaterial(0, tokenMaterialComputer);
		} break;
	}
}

