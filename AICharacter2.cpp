// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "AICharacter2.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter2::AAICharacter2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensing2 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing2"));
}

// Called when the game starts or when spawned
void AAICharacter2::BeginPlay()
{
	Super::BeginPlay();
	
	
	PawnSensing2->OnSeePawn.AddDynamic(this, &AAICharacter2::SeePawn);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc.Location);

		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter2::BeginPlay, 2.f);
	}
}

// Called every frame
void AAICharacter2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAICharacter2::SeePawn(APawn* Pawn)
{
	AHideAndSeekCharacter* AISee2 = Cast<AHideAndSeekCharacter>(Pawn);

	if (AISee2)
	{
		GetWorldTimerManager().ClearTimer(Timer);

		
		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter2::BeginPlay, 2.0f);
	}

}


