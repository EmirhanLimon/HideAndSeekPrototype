// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedPlusCollision.h"

// Sets default values
ASpeedPlusCollision::ASpeedPlusCollision()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SpeedPlus = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpeedPlus->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASpeedPlusCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpeedPlusCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

