// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "PointCollision.h"
//#include "Components/BoxComponent.h"

// Sets default values
APointCollision::APointCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Deneme = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Deneme->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APointCollision::BeginPlay()
{
	Super::BeginPlay();
	
//	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APointCollision::BeginOverlap);
}

// Called every frame
void APointCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





