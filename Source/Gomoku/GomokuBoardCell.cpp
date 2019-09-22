// Fill out your copyright notice in the Description page of Project Settings.


#include "GomokuBoardCell.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
AGomokuBoardCell::AGomokuBoardCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh0"));
	mesh->SetStaticMesh(ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/Shapes/Cell.Cell")).Get());
	mesh->SetMaterial(0, ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/Materials/CellMaterial.CellMaterial")).Get());
	mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	dummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = dummyRoot;
	mesh->SetupAttachment(dummyRoot);
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
	mesh->SetWorldScale3D(FVector(scale, scale, scale));
}

