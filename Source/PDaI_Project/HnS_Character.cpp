// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Character.h"
#include "HnS_Weapon.h"
#include "HnS_Bullet.h"

void AHnS_Character::SetupMesh()
{
	UMeshComponent* meshRef = this->GetMesh();
	meshRef->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
}

void AHnS_Character::SetupMovement()
{
	this->bUseControllerRotationYaw = false;
	charMovement = this->GetCharacterMovement();
	charMovement->bOrientRotationToMovement = true;
	charMovement->bRequestedMoveUseAcceleration = false;
}

void AHnS_Character::CreateWeapon()
{
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet spawn points"));
	SpawnLocation->SetupAttachment(GetMesh());
}

float AHnS_Character::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//DamageAmount = 10;
	HP -= DamageAmount;
	if (HP <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}

// Sets default values
AHnS_Character::AHnS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupMovement();
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet spawn points"));
	SpawnLocation->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AHnS_Character::BeginPlay()
{
	Super::BeginPlay();
	//check(GEngine != nullptr);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TestCharacter."));
	// Display a debug message for five seconds. 
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TestCharacter."));
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
	SpawnParams.Owner = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_Bullet>(BulletToSpawn,SpawnLocation->GetComponentLocation() + FVector(0, 0, 0) , GetActorRotation(), SpawnParams);

	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet debug!"));
	}

	return SpawnedActor;
}

