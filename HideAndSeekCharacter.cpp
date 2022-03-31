// Copyright Epic Games, Inc. All Rights Reserved.
#include "Perception/PawnSensingComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "HideAndSeekCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Components/SphereComponent.h"
#include "AICharacter1.h"
#include "AICharacter2.h"
#include "AICharacter3.h"
#include "AICharacter4.h"
#include "AICharacter5.h"
#include "PointCollision.h"
#include "SpeedPlusCollision.h"
#include "SpeedNegativeCollision.h"
#include "SwordCollision.h"



//////////////////////////////////////////////////////////////////////////
// AHideAndSeekCharacter

AHideAndSeekCharacter::AHideAndSeekCharacter()
{
	
	
	HideAndSeekCharacterCompCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HideAndSeekCharacterCompCapsuleCpp"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHideAndSeekCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHideAndSeekCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHideAndSeekCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AHideAndSeekCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AHideAndSeekCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AHideAndSeekCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AHideAndSeekCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AHideAndSeekCharacter::OnResetVR);
}
void AHideAndSeekCharacter::BeginPlay()
{
	Super::BeginPlay();

	//HideAndSeekCharacterComp->OnComponentBeginOverlap.AddDynamic(this, &AHideAndSeekCharacter::BeginOverlap);
	HideAndSeekCharacterCompCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHideAndSeekCharacter::BeginOverlap);

}



void AHideAndSeekCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAICharacter1* Carp1 = Cast<AAICharacter1>(OtherActor);
	AAICharacter2* Carp2 = Cast<AAICharacter2>(OtherActor);
	AAICharacter3* Carp3 = Cast<AAICharacter3>(OtherActor);
	AAICharacter4* Carp4 = Cast<AAICharacter4>(OtherActor);
	AAICharacter5* Carp5 = Cast<AAICharacter5>(OtherActor);
	APointCollision* Point = Cast<APointCollision>(OtherActor);
	ASpeedPlusCollision* SpeedPlus = Cast<ASpeedPlusCollision>(OtherActor);
	ASpeedNegativeCollision* SpeedNegative = Cast<ASpeedNegativeCollision>(OtherActor);
	ASwordCollision* SwordPlus = Cast<ASwordCollision>(OtherActor);
	

	if (Carp1 || Carp2 || Carp3 || Carp4 || Carp5)
	{
		if (TakeSword == 1 && (Carp1 || Carp2 || Carp3 || Carp4 || Carp5))
		{
			AIScore++;

			if (Carp1)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("AI KILL"));
				TakeSword = 0;
				Carp1->Destroy();
				
			}
			if (Carp2)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("AI KILL"));
				TakeSword = 0;
				Carp2->Destroy();
				
			}
			if (Carp3)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("AI KILL"));
				TakeSword = 0;
				Carp3->Destroy();
			}
			if (Carp4)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("AI KILL"));
				TakeSword = 0;
				Carp4->Destroy();
			}
			if (Carp5)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, TEXT("AI KILL"));
				TakeSword = 0;
				Carp5->Destroy();
			}
			
		}
		else
		{
			GameOver = 1;
		}
		
		
	}
	if (Point) 
	{
		Score++;
		
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Skor : %i"), Score));
		Point->Destroy();
		Tetik = 0;
	}
	if (SpeedPlus)
	{
		
		GetCharacterMovement()->MaxWalkSpeed = 4000;
		SpeedPlus->Destroy();
		Tetik2 = 0;
		GetWorldTimerManager().SetTimer(Timer, this, &AHideAndSeekCharacter::SpeedPlusFun, 3.0f);
		
		
	}
	if (SpeedNegative)
	{
		GetCharacterMovement()->MaxWalkSpeed = 1250;
		SpeedNegative->Destroy();
		Tetik2 = 0;
		GetWorldTimerManager().SetTimer(Timer, this, &AHideAndSeekCharacter::SpeedNegativeFun, 3.0f);
	}
	if (SwordPlus)
	{
		if (TakeSword == 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Aldim"));
			SwordTetik = 0;
			TakeSword = 1;
			SwordPlus->Destroy();
		}
		
	}
	
	

}
void AHideAndSeekCharacter::SpeedPlusFun()
{
	GetCharacterMovement()->MaxWalkSpeed = 2000;
}
void AHideAndSeekCharacter::SpeedNegativeFun()
{
	GetCharacterMovement()->MaxWalkSpeed = 2000;
}



void AHideAndSeekCharacter::OnResetVR()
{
	
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AHideAndSeekCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AHideAndSeekCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AHideAndSeekCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHideAndSeekCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHideAndSeekCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AHideAndSeekCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
