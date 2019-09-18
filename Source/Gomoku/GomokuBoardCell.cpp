// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuBoardCell.h"

// Sets default values
AGomokuBoardCell::AGomokuBoardCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

