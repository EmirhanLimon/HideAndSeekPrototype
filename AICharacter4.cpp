// Fill out your copyright notice in the Description page of Project Settings.
#include "HideAndSeekCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AICharacter4.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter4::AAICharacter4()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PawnSensing4 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing4"));
}

// Called when the game starts or when spawned
void AAICharacter4::BeginPlay()
{
	Super::BeginPlay();

	
	PawnSensing4->OnSeePawn.AddDynamic(this, &AAICharacter4::SeePawn);
	PawnSensing4->OnHearNoise.AddDynamic(this, &AAICharacter4::OnHearNoise);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(11560.f,1890.f,160.f));

		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter4::NewMovement, 4.f);
		GetCharacterMovement()->MaxWalkSpeed = 1500;
		
	}
	
}

void AAICharacter4::NewMovement()
{
	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(8649.f,-2120.f,260.f));


		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter4::BeginPlay, 4.f);
	}
}

// Called every frame
void AAICharacter4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AAICharacter4::SeePawn(APawn* Pawn)
{
	AHideAndSeekCharacter* AISee4 = Cast<AHideAndSeekCharacter>(Pawn);

	if (AISee4)
	{
		GetWorldTimerManager().ClearTimer(Timer);

		
		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),-1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter4::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2500;
	}

}
void AAICharacter4::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AHideAndSeekCharacter* AIHear4 = Cast<AHideAndSeekCharacter>(OtherActor);

	if (AIHear4)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter4::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2000;
	}
}