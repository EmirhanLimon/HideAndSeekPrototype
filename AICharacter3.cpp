// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "Components/BoxComponent.h"
#include "AICharacter3.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	PawnSensing3->OnHearNoise.AddDynamic(this, &AAICharacter3::OnHearNoise);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(-5770.f,-350.f,160.f));

		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter3::NewMovement, 4.f);
		GetCharacterMovement()->MaxWalkSpeed = 1500;
	}
}
void AAICharacter3::NewMovement()
{
	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(1059.f,-440.f,288.f));


		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter3::BeginPlay, 4.f);
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
		GetCharacterMovement()->MaxWalkSpeed = 2500;
	}

}
void AAICharacter3::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AHideAndSeekCharacter* AIHear3 = Cast<AHideAndSeekCharacter>(OtherActor);

	if (AIHear3)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter3::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2000;
	}
}
