// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuBoard.h"

#include <GenericPlatformMath.h>

#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include "Engine/Engine.h"
#define print(text, length) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, length, FColor::White, text)

// Sets default values
AGomokuBoard::AGomokuBoard() 
	: lastPlayerCellX(0)
	, lastPlayerCellY(0)
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

	float xyAxisScale = BoardSize * (CellScale / 100.0f);
	mesh->SetWorldScale3D(FVector(xyAxisScale, xyAxisScale, 1.0f));

	Super::BeginPlay();

	float xyAxisOffset = (BoardSize * CellScale) / 2.0f - CellScale / 2.0f;
	FVector offset = FVector(xyAxisOffset, xyAxisOffset, 0.0f) + GetActorLocation();
	
	for (int32 y = 0; y < BoardSize; y++)
	{
		for (int32 x = 0; x < BoardSize; x++)
		{
			FVector cell_position = FVector(x * CellScale, y * CellScale, 0.0f) - offset;
			AGomokuBoardCell* cell = GetWorld()->SpawnActor<AGomokuBoardCell>(cell_position, FRotator(0, 0, 0));
			cell->SetScale(CellScale / 100.0f);

			cell->X = x;
			cell->Y = y;
			cell->ParentBoard = this;

			cells.Add(cell);
		}
	}

	// Horizontal lines
	for (int y = 0; y < BoardSize; ++y)
	{
		TArray<AGomokuBoardCell*> horizontalLine;
		for (int x = 0; x < BoardSize; ++x)
		{
			horizontalLine.Add(cells[getCellIndex(x, y)]);
		}

		allLines.Add(horizontalLine);
		horizontalLines.Add(horizontalLine);
	}
	
	// Vertical lines
	for (int x = 0; x < BoardSize; ++x)
	{
		TArray<AGomokuBoardCell*> verticalLine;
		for (int y = 0; y < BoardSize; ++y)
		{
			verticalLine.Add(cells[getCellIndex(x, y)]);
		}

		allLines.Add(verticalLine);
		verticalLines.Add(verticalLine);
	}

	// Left hand orthogonal lines
	for (int i = (-BoardSize + 1); i < BoardSize; ++i)
	{
		int length = BoardSize - abs(i);
		if (length < 5)
		{
			continue;
		}

		TArray<AGomokuBoardCell*> leftHandOrthoLine;

		int x = FGenericPlatformMath::Max(i, 0);
		int y = abs(FGenericPlatformMath::Min(i, 0));

		for (int step = 0; step < length; ++step, ++x, ++y)
		{
			leftHandOrthoLine.Add(cells[getCellIndex(x, y)]);
		}

		allLines.Add(leftHandOrthoLine);
		leftHandOrthoLines.Add(leftHandOrthoLine);
	}

	// Right hand orthogonal lines
	for (int i = 0; i < (BoardSize * 2) - 1; ++i)
	{
		int length = FGenericPlatformMath::Min(i + 1, BoardSize) - FGenericPlatformMath::Max((i + 1) - BoardSize, 0);
		if (length < 5)
		{
			continue;
		}

		TArray<AGomokuBoardCell*> rightHandOrthoLine;

		int x = FGenericPlatformMath::Min(i, BoardSize - 1);
		int y = (x + 1) - length;

		for (int step = 0; step < length; ++step, --x, ++y)
		{
			rightHandOrthoLine.Add(cells[getCellIndex(x, y)]);
		}

		allLines.Add(rightHandOrthoLine);
		rightHandOrthoLines.Add(rightHandOrthoLine);
	}
}

// Called every frame
void AGomokuBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGomokuBoard::OnPlayerActivatedCell(int x, int y)
{
	bool playerFiveInARow = false;
	for (const TArray<AGomokuBoardCell*>& line : allLines)
	{
		playerFiveInARow = fiveInARow(line, AGomokuBoardCell::State::Player);
		if (playerFiveInARow)
		{
			break;
		}
	}

	if (playerFiveInARow)
	{
		print(FString("Player wins!!!"), 100.0);
		return;
	}

	// TODO: Implement real AI logic with states
	int playerMoveVectorX = x - lastPlayerCellX;
	int playerMoveVectorY = y - lastPlayerCellY;

	if (playerMoveVectorX != 0)
	{
		playerMoveVectorX /= playerMoveVectorX;
	}
	if (playerMoveVectorY != 0)
	{
		playerMoveVectorY /= playerMoveVectorY;
	}

	// Nudge in random direction while totally zero (probability theory states that this could enter an infinite loop)
	while (playerMoveVectorX == 0 && playerMoveVectorY == 0)
	{
		playerMoveVectorX = (rand() % 3) - 1;
		playerMoveVectorY = (rand() % 3) - 1;
	}

	print(FString("playerMoveVectorX: ") + FString::FromInt(playerMoveVectorX) + FString(", playerMoveVectorY: ") + FString::FromInt(playerMoveVectorY), 10);

	auto validMoveCell = [](TArray<AGomokuBoardCell*> cells, int cellIndex) -> bool 
		{ 
			return cellIndex >= 0 && cellIndex < cells.Num() &&
			(cells[cellIndex]->GetState() == AGomokuBoardCell::State::Disabled ||
			cells[cellIndex]->GetState() == AGomokuBoardCell::State::Highlighted);
		};

	bool computerMoved = false;
	int cellIndex = getCellIndex(x + playerMoveVectorX, y + playerMoveVectorY);
	
	if (!validMoveCell(cells, cellIndex))
	{
		playerMoveVectorX *= -1;
		playerMoveVectorY *= -1;

		int stepX = x;
		int stepY = y;

		while (stepX >= 0 && stepX < BoardSize && stepY >= 0 && stepY < BoardSize)
		{
			stepX += playerMoveVectorX;
			stepY += playerMoveVectorY;

			cellIndex = getCellIndex(stepX, stepY);

			if (validMoveCell(cells, cellIndex))
			{
				computerMoved = true;
				break;
			}
		}
	}
	else
	{
		computerMoved = true;
	}

	if (computerMoved)
	{
		cells[cellIndex]->SetState(AGomokuBoardCell::State::Computer);
	}

	lastPlayerCellX = x;
	lastPlayerCellY = y;
	//

	bool computerFiveInARow = false;
	for (const TArray<AGomokuBoardCell*>& line : allLines)
	{
		computerFiveInARow = fiveInARow(line, AGomokuBoardCell::State::Computer);
		if (computerFiveInARow)
		{
			break;
		}
	}

	if (computerFiveInARow)
	{
		print(FString("Computer wins!!!"), 100.0);
		return;
	}
}

int AGomokuBoard::getCellIndex(int x, int y)
{
	return y * BoardSize + x;
}

bool AGomokuBoard::fiveInARow(const TArray<AGomokuBoardCell*>& line, AGomokuBoardCell::State state)
{
	int currentLength = 0;
	int longest = 0;
	for (int i = 0; i < line.Num(); ++i)
	{
		if (line[i]->GetState() == state)
		{
			currentLength += 1;
		}
		else
		{
			// Discard result higher than 5 in standard gomoku
			if (currentLength <= 5)
			{
				longest = FGenericPlatformMath::Max(longest, currentLength);
			}
			
			currentLength = 0;
		}

		// == for standard gomoku, >= for free-style according to wiki
		if (longest == 5)
		{
			return true;
		}
	}

	return false;
}

