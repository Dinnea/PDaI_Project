// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HnS_Weapon.h"
#include "HnS_Bullet.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Perception/AISense_Sight.h>



void AHnS_Character::SetupStimulusSouce()
{
	stimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));

	if (stimulusSource) 
	{
		stimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		stimulusSource->RegisterWithPerceptionSystem();
	}
}

// Sets default values
AHnS_Character::AHnS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//setup movement and orientation
	//TODO: make it into a functon
	this->bUseControllerRotationYaw = false;
	charMovement = this->GetCharacterMovement();
	charMovement->bOrientRotationToMovement = true;
	charMovement->bRequestedMoveUseAcceleration = false;
	meshRef = this->GetMesh();
	meshRef->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, 0.f, 0.f));

	//setup camera
	//TODO: turn it into a function
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

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet spawn points"));
	SpawnLocation->SetupAttachment(GetMesh());
	SetupStimulusSouce();

	
}

// Called when the game starts or when spawned
void AHnS_Character::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);
	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TestCharacter."));
	AHnS_Weapon* weaponPtr = Cast<AHnS_Weapon>(Weapon->GetChildActor());
	if(weaponPtr)
	{
		weaponPtr->SetPlayerPointer(this);
	}
	
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

AActor* AHnS_Character::ShootBullet()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_Bullet>(BulletToSpawn,SpawnLocation->GetComponentLocation(),GetActorRotation());

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet debug!"));
	}

	return SpawnedActor;
}

