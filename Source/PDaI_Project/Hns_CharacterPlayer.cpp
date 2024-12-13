// Fill out your copyright notice in the Description page of Project Settings.


#include "Hns_CharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Perception/AISense_Sight.h>
#include <Kismet/GameplayStatics.h>
#include <HnS_GameModeBase.h>
#include "HnS_GameInstance.h"

void AHns_CharacterPlayer::SetupStimulusSouce()
{
	stimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));

	if (stimulusSource)
	{
		stimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		stimulusSource->RegisterWithPerceptionSystem();
	}
}

void AHns_CharacterPlayer::SetupCamera()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = false;
	springArm->TargetArmLength = 800.f;
	springArm->SetUsingAbsoluteRotation(true);
	springArm->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;
}

AHns_CharacterPlayer::AHns_CharacterPlayer()
{
	SetupMesh();
	SetupMovement();
	SetupCamera();
	SetupStimulusSouce();
	//CreateWeapon();
}

void AHns_CharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AHns_CharacterPlayer::Die()
{
	Super::Die();
	/*if (auto* const gameModePtr = Cast<AHnS_GameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gameModePtr->isGameOver = true;
	}*/

	if (auto* const gameInstancePtr = Cast<UHnS_GameInstance>(GetGameInstance())) 
	{
		gameInstancePtr->isGameOver = false;
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));

}

void AHns_CharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHns_CharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
