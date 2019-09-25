// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GomokuBoardCell.generated.h"

// Forward declaration(s)
class AGomokuBoard;

UCLASS()
class GOMOKU_API AGomokuBoardCell : public AActor
{
	GENERATED_BODY()
	
public:	

	enum class State
	{
		Disabled,
		Highlighted,
		Player,
		Computer
	};

	// Sets default values for this actor's properties
	AGomokuBoardCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetScale(float scale);

	AGomokuBoardCell::State GetState() { return currentState; }
	void SetState(AGomokuBoardCell::State state);

public:

	UPROPERTY()
	AGomokuBoard* ParentBoard;

	int X;
	int Y;

private:

	State currentState;

	USceneComponent* dummyRoot;
	UStaticMeshComponent* gridMesh;

	UStaticMeshComponent* tokenMesh;
	UMaterial* tokenMaterial;
	UMaterialInstance* tokenMaterialPlayer;
	UMaterialInstance* tokenMaterialComputer;

};
