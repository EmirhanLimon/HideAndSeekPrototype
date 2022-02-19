// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedNegativeCollision.h"

// Sets default values
ASpeedNegativeCollision::ASpeedNegativeCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpeedNegative = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SpeedNegative->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASpeedNegativeCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpeedNegativeCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

