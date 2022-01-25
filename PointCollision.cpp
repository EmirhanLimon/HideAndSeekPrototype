// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "PointCollision.h"
//#include "Components/BoxComponent.h"

// Sets default values
APointCollision::APointCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//oluþturduk
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCompCpp"));
	//Karaktere bagladýk
	//BoxCollision->SetupAttachment(GetComponents());
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

/*void APointCollision::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AHideAndSeekCharacter* CollisionScore = Cast<AHideAndSeekCharacter>(OtherActor);

	
	
	if (CollisionScore) {
		
		Score++;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Skor : %i"), Score));
		//FTimerHandle Timer;
		//GetWorldTimerManager().SetTimer(Timer, this, &APointCollision::ScoreFunction, 0.1f);
		
	}
	
	
}*/



