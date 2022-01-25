// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "AICharacter1.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"
// Sets default values



AAICharacter1::AAICharacter1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	
	//Karaktere bagladýk
	//AIBoxCollision1->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAICharacter1::BeginPlay()
{
	

	Super::BeginPlay();

	
	
	PawnSensing->OnSeePawn.AddDynamic(this, &AAICharacter1::SeePawn);
	

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(NavLoc.Location);
		
		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::BeginPlay,2.0f);
		
	}
	
	
}
void AAICharacter1::SeePawn(APawn* Pawn)
{
	AHideAndSeekCharacter* AISee1 = Cast<AHideAndSeekCharacter>(Pawn);

	

	if (AISee1)
	{	
		GetWorldTimerManager().ClearTimer(Timer);
		
		
		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),-1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::BeginPlay, 2.0f);
		
	}
	
}




void AAICharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}





