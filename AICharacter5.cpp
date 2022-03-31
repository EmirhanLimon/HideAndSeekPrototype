// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeekCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AICharacter5.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAICharacter5::AAICharacter5()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	PawnSensing5 = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing5"));
}

// Called when the game starts or when spawned
void AAICharacter5::BeginPlay()
{
	Super::BeginPlay();

	
	PawnSensing5->OnSeePawn.AddDynamic(this, &AAICharacter5::SeePawn);
	PawnSensing5->OnHearNoise.AddDynamic(this, &AAICharacter5::OnHearNoise);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	FNavLocation NavLoc;
	NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 10000.f, NavLoc);

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(11610.f,-1400.f,160.f));

		
		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter5::NewMovement, 4.f);
		GetCharacterMovement()->MaxWalkSpeed = 1500;
	}
	
}
void AAICharacter5::NewMovement()
{

	AIC_Ref = Cast<AAIController>(GetController());
	if (AIC_Ref)
	{
		AIC_Ref->MoveToLocation(FVector(8549.f,3340.f,288.f));


		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter5::BeginPlay, 4.0f);

	}
}

// Called every frame
void AAICharacter5::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AAICharacter5::SeePawn(APawn*Pawn)
{
	AHideAndSeekCharacter* AISee5 = Cast<AHideAndSeekCharacter>(Pawn);

	if (AISee5)
	{
		GetWorldTimerManager().ClearTimer(Timer);

		
		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(),-1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter5::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2500;
	}


}
void AAICharacter5::OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume)
{
	AHideAndSeekCharacter* AIHear5 = Cast<AHideAndSeekCharacter>(OtherActor);

	if (AIHear5)
	{
		GetWorldTimerManager().ClearTimer(Timer);


		AIC_Ref->MoveToLocation(GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), -1);

		GetWorldTimerManager().SetTimer(Timer, this, &AAICharacter5::BeginPlay, 2.0f);
		GetCharacterMovement()->MaxWalkSpeed = 2000;
	}
}
