// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "HnS_Bullet.h"
#include "HnS_WAbility.h"
#include "Hns_CharacterPlayer.h"

// Sets default values
AHnS_Weapon::AHnS_Weapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHnS_Weapon::SetReady(bool value)
{
	ready = value;
}

AActor* AHnS_Weapon::Attack()
{
	if (ready) 
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Player;
		SpawnParams.Owner = this;
		AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_Bullet>(BulletToSpawn, spawnLocation->GetComponentLocation() + FVector(0, 0, 0), Player->GetActorRotation(), SpawnParams);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Attack debug"));
		}*/

		SetReady(false);

		FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Weapon::SetReady, true);
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, cooldown, false);

		return SpawnedActor;
	}
	return nullptr;
}

AActor* AHnS_Weapon::W()
{
	cachedDest_W = controlledPlayer->getClickLocation();
	//cachedDest_W = FVector::ZeroVector;
	controlledPlayer->rotatePlayer(cachedDest_W);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Player;
	SpawnParams.Owner = this;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(spawnLocation->GetComponentLocation()).ToString());
	AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_WAbility>(WToSpawn, spawnLocation->GetComponentLocation() + FVector(0, 0, 250), Player->GetActorRotation(), SpawnParams);
	if (SpawnedActor == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("W nullptr"));
	}
	return SpawnedActor;
}

// Called when the game starts or when spawned
void AHnS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	//Player = UGameplayStatics::GetPlayerCharacter(this,0)
	
}


void AHnS_Weapon::SetPlayerPointer(ACharacter *PlayerPointer)
{
	Player = PlayerPointer;
}

void AHnS_Weapon::SetProjectileSpawnLocation(USceneComponent* pSpawnLocation)
{
	this->spawnLocation = pSpawnLocation;
}


// Called every frame
void AHnS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

