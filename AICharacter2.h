// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AICharacter2.generated.h"

class UPawnSensingComponent;

UCLASS()
class HIDEANDSEEK_API AAICharacter2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		UPawnSensingComponent* PawnSensing2;
	UFUNCTION()
		void SeePawn(APawn* Pawn);

	
	
	UPROPERTY()
		AAIController* AIC_Ref;
	UPROPERTY(EditDefaultsOnly)
		FTimerHandle Timer;
	
};
