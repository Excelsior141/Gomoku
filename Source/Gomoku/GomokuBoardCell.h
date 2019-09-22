// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GomokuBoardCell.generated.h"

UCLASS()
class GOMOKU_API AGomokuBoardCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGomokuBoardCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetScale(float scale);

private:

	USceneComponent* dummyRoot;
	UStaticMeshComponent* mesh;
};
