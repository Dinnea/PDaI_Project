// Fill out your copyright notice in the Description page of Project Settings.

#include "HnS_Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "HnS_Bullet.h"
#include "Hns_CharacterPlayer.h"
#include "HnS_RBullet.h"

// Sets default values
AHnS_Weapon::AHnS_Weapon()
{
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AHnS_Weapon::Execute()
{
	if(!Super::Execute()) return false;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = user;
	SpawnParams.Owner = this;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Weapon execute"));
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(objectToSpawn, spawnLocation->GetComponentLocation() + Offset, user->GetActorRotation(), SpawnParams);
	return true;
}

bool AHnS_Weapon::ExecuteRSubclass()
{
	if (!Super::ExecuteRSubclass()) return false;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = user;
	SpawnParams.Owner = this;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Weapon execute R"));
	AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_RBullet>(r_objectToSpawn, spawnLocation->GetComponentLocation() + Offset, user->GetActorRotation(), SpawnParams);
	return true;
}

// Called when the game starts or when spawned
void AHnS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	//Player = UGameplayStatics::GetPlayerCharacter(this,0)
	
}

void AHnS_Weapon::SetAbilitySpawnLocation(USceneComponent* pSpawnLocation)
{
	this->spawnLocation = pSpawnLocation;
}


// Called every frame
void AHnS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

