// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollision.generated.h"

UCLASS()
class HIDEANDSEEK_API APointCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointCollision();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Deneme;
	//UPROPERTY(EditDefaultsOnly)
	//class UBoxComponent* BoxCollision;

	//UFUNCTION()
	//void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
		//int Score;
	//UFUNCTION()
		//void ScoreFunction();
	
};
