// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GomokuBoardCell.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GomokuBoard.generated.h"

UCLASS()
class GOMOKU_API AGomokuBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGomokuBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnPlayerActivatedCell(int x, int y);

public:

	UPROPERTY(Category=Board, EditAnywhere, meta = (ClampMin = "8", ClampMax = "50", UIMin = "8", UIMax = "50"))
	int32 BoardSize;

	UPROPERTY(Category=Board, EditAnywhere, meta = (ClampMin = "1.0", ClampMax = "100.0", UIMin = "1.0", UIMax = "100.0"))
	float CellScale;

private:

	int getCellIndex(int x, int y);

	bool fiveInARow(const TArray<AGomokuBoardCell*>& line, AGomokuBoardCell::State state);

private:

	USceneComponent* dummyRoot;
	UStaticMeshComponent* mesh;

	TArray<AGomokuBoardCell*> cells;

	int lastPlayerCellX;
	int lastPlayerCellY;

	TArray<TArray<AGomokuBoardCell*>> allLines;
	TArray<TArray<AGomokuBoardCell*>> verticalLines;
	TArray<TArray<AGomokuBoardCell*>> horizontalLines;
	TArray<TArray<AGomokuBoardCell*>> leftHandOrthoLines;
	TArray<TArray<AGomokuBoardCell*>> rightHandOrthoLines;
};
