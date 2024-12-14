// Fill out your copyright notice in the Description page of Project Settings.


#include "Hns_CharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HnS_PlayerController.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Perception/AISense_Sight.h>
#include <Kismet/GameplayStatics.h>
#include "HealArea.h"

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

void AHns_CharacterPlayer::death()
{
	FTimerDelegate dDelegate = FTimerDelegate::CreateUObject(this, &AHns_CharacterPlayer::deathDelay);
	FTimerHandle dTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(dTimerHandle, dDelegate, 2, false);
}

void AHns_CharacterPlayer::deathDelay()
{
	p_controller->setDead(false);
	GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenu"));
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
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;
	AActor* heal_aura = GetWorld()->SpawnActor<AHealArea>(healAura_spawn, FVector(-6029, -1342, 202), FRotator(0,0,0), SpawnParams);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Character Player beginplay"));
}

void AHns_CharacterPlayer::Die()
{
	Super::Die();
	playDeathAnim = true;
	GetCharacterMovement()->DisableMovement();
	p_controller = Cast<AHnS_PlayerController>(GetController());
	p_controller->setDead(true);
}

void AHns_CharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHns_CharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
