// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuBoard.h"

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AGomokuBoard::AGomokuBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh0"));
	mesh->SetStaticMesh(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/Shapes/Board.Board")).Get());
	mesh->SetMaterial(0, ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/Materials/BoardMaterial.BoardMaterial")).Get());

	dummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = dummyRoot;
	mesh->SetupAttachment(dummyRoot);
}

// Called when the game starts or when spawned
void AGomokuBoard::BeginPlay()
{
	mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	mesh->SetWorldScale3D(FVector(Width * (CellSize / 100.0f), Height * (CellSize / 100.0f), 1.0f));

	Super::BeginPlay();

	FVector offset = FVector((Width * CellSize) / 2.0f - CellSize / 2.0f, (Height * CellSize) / 2.0f - CellSize / 2.0f, 0.0f) + GetActorLocation();
	
	for (int32 y = 0; y < Height; y++)
	{
		for (int32 x = 0; x < Width; x++)
		{
			FVector cell_position = FVector(x * CellSize, y * CellSize, 0.0f) - offset;
			AGomokuBoardCell* cell = GetWorld()->SpawnActor<AGomokuBoardCell>(cell_position, FRotator(0, 0, 0));
			cell->SetScale(CellSize / 100.0f);

			cells.Add(cell);
		}
	}
	
}

// Called every frame
void AGomokuBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

