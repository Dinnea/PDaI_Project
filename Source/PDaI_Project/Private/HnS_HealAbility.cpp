// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_HealAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include <NiagaraFunctionLibrary.h>

bool AHnS_HealAbility::Execute()
{
	if (!Super::Execute()) return false;

	AActor* target = ReturnNearestNeedsHealing();
	UGameplayStatics::ApplyDamage(target, -damage, GetInstigatorController(), this, DamageType);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), vfx, target->GetActorLocation(), target->GetActorRotation());
	return true;
}

AHnS_HealAbility::AHnS_HealAbility()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
}

void AHnS_HealAbility::BeginPlay()
{
	Super::BeginPlay();


	CollisionSphere->SetSphereRadius(range);
	SetActorLocation(GetActorLocation() + FVector(0, 0, 10000));

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_HealAbility::BeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AHnS_HealAbility::EndOverlap);

	FTimerDelegate collisionDelegate = FTimerDelegate::CreateUObject(this, &AHnS_HealAbility::StartCollisionChecking);
	GetWorld()->GetTimerManager().SetTimerForNextTick(collisionDelegate);
	
}

void AHnS_HealAbility::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* const enemy = Cast<AHnS_BaseEnemy>(OtherActor))
	{
		enemiesInRange.Add(enemy);
	}
}

void AHnS_HealAbility::EndOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto* const enemy = Cast<AHnS_BaseEnemy>(OtherActor))
	{
		enemiesInRange.Remove(enemy);
	}
}

ACharacter* AHnS_HealAbility::ReturnNearestNeedsHealing()
{

	if (IsHPBelowThreshold(Cast<AHnS_Character>(user))) return user;

	AHnS_BaseEnemy* nearest = nullptr;

	FVector thisLocation = GetActorLocation();

	float lowestDist = 9999999999999;

	for (AHnS_BaseEnemy* enemyToCheck : enemiesInRange) 
	{
		if (IsHPBelowThreshold(enemyToCheck)) 
		{
			FVector distanceVec = enemyToCheck->GetActorLocation() - thisLocation;
			float distance = distanceVec.Length();

			if (distance < lowestDist) 
			{
				lowestDist = distance;
				nearest = enemyToCheck;
			}
		}
		
	}

	return nearest;
}

bool AHnS_HealAbility::IsHPBelowThreshold(AHnS_Character* tar)
{
	float hpPercentCurrent = (tar->HP) / (tar->MaxHP);

	if (hpPercentCurrent <= hpThreshold)
	{
		return true;
	}
	else return false;
}

void AHnS_HealAbility::StartCollisionChecking()
{
	SetActorLocation(GetActorLocation() - FVector(0, 0, 10000));
}
