// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter1.generated.h"

class UPawnSensingComponent;

UCLASS()
class HIDEANDSEEK_API AAICharacter1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPawnSensingComponent* PawnSensing;

	UFUNCTION()
		void SeePawn(APawn* Pawn);
	UFUNCTION()
		void NewMovement();
	UFUNCTION()
		void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
		AAIController* AIC_Ref;
	
	UPROPERTY(EditDefaultsOnly)
		FTimerHandle Timer;
	
};
