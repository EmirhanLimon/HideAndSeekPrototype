// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "Components/BoxComponent.h"
#include "AICharacter3.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter3::AAICharacter3()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	PawnSensing3 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing3"));
}

// Called when the game starts or when spawned
void AAICharacter3::BeginPlay()
{
	Super::BeginPlay();
	
	
	PawnSensing3->OnSeePawn.AddDynamic(this, &AAICharacter3::SeePawn);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc.Location);

		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter3::BeginPlay, 2.f);
	}
}

// Called every frame
void AAICharacter3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAICharacter3::SeePawn(APawn* Pawn)
{
	AHideAndSeekCharacter* AISee3 = Cast<AHideAndSeekCharacter>(Pawn);

	if (AISee3)
	{
		GetWorldTimerManager().ClearTimer(Timer);

		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),-1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter3::BeginPlay, 2.0f);
	}

}

