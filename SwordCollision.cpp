// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordCollision.h"

// Sets default values
ASwordCollision::ASwordCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Sword->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ASwordCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwordCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

