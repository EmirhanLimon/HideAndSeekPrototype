// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "AICharacter1.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"




AAICharacter1::AAICharacter1()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	
	
}


void AAICharacter1::BeginPlay()
{
	

	Super::BeginPlay();

	
	
	PawnSensing->OnSeePawn.AddDynamic(this, &AAICharacter1::SeePawn);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAICharacter1::OnHearNoise);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(-7750.f, 3480.f,  160.f));
		
		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::NewMovement,4.0f);
		GetCharacterMovement()->MaxWalkSpeed = 1500;
	}
	
	
}
void AAICharacter1::NewMovement()
{
	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(820.f,3410.f,218.f));


		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::BeginPlay, 4.0f);

	}
}
void AAICharacter1::SeePawn(APawn* Pawn)
{
	AHideAndSeekCharacter* AISee1 = Cast<AHideAndSeekCharacter>(Pawn);

	

	if (AISee1)
	{	
		GetWorldTimerManager().ClearTimer(Timer);
		
		
		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),-1.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2500;
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::BeginPlay, 2.0f);
		
	}
	
}

void AAICharacter1::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AHideAndSeekCharacter* AIHear1 = Cast<AHideAndSeekCharacter>(OtherActor);

	if (AIHear1)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter1::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2000;
	}
}





void AAICharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}





