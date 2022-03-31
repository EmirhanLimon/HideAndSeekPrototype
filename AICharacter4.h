// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter4.generated.h"

class UPawnSensingComponent;

UCLASS()
class HIDEANDSEEK_API AAICharacter4 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter4();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY()
		AAIController* AIC_Ref;

	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPawnSensingComponent* PawnSensing4;
	UFUNCTION()
		void SeePawn(APawn* Pawn);
	UFUNCTION()
		void OnHearNoise(APawn* OtherActor, const FVector& Location, float Volume);
	UFUNCTION()
		void NewMovement();
	
	UPROPERTY(EditDefaultsOnly)
		FTimerHandle Timer;
	
};
