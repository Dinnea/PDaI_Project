// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = root;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);

	
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AHnS_BaseEnemy* AEnemySpawner::SpawnAtSpawnerLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn)
{
	return SpawnAtLocation(enemyToSpawn, this->GetActorLocation(), this->GetActorRotation());
}

AHnS_BaseEnemy* AEnemySpawner::SpawnAtRandomLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn, float radius)
{
	FNavLocation location;
 	if (UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		navSystem->GetRandomPointInNavigableRadius(this->GetActorLocation(), radius, location);
	}
	/*check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::SanitizeFloat(location.Location.X) + ", " +
															FString::SanitizeFloat(location.Location.Y) + ", " +
															FString::SanitizeFloat(location.Location.Z));*/
	return SpawnAtLocation(enemyToSpawn, location.Location, this->GetActorRotation());
}

AHnS_BaseEnemy* AEnemySpawner::SpawnAtLocation(TSubclassOf<AHnS_BaseEnemy> enemyToSpawn, FVector location, FRotator rotation)
{
	AHnS_BaseEnemy* spawnedEnemy = GetWorld()->SpawnActor<AHnS_BaseEnemy>(enemyToSpawn, location, rotation);
	return spawnedEnemy;
}

FVector AEnemySpawner::GetRandomLocation(float radius)
{
	FNavLocation location;
	if (UNavigationSystemV1* const navSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		navSystem->GetRandomPointInNavigableRadius(this->GetActorLocation(), radius, location);
	}

	return location.Location;
}


