// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AHnS_Character::AHnS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bUseControllerRotationYaw = false;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(RootComponent);
	springArm->bUsePawnControlRotation = false;
	springArm->TargetArmLength = 800.f;
	springArm->SetUsingAbsoluteRotation(true);
	springArm->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	camera->bUsePawnControlRotation = false;

	charMovement = this->GetCharacterMovement();
	charMovement->bOrientRotationToMovement = true;

	meshRef = this->GetMesh();
	meshRef->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
}

// Called when the game starts or when spawned
void AHnS_Character::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TestCharacter."));
	
}

// Called every frame
void AHnS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHnS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

