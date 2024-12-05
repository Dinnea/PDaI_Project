// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_WAbility.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include <PDaI_Project/HnS_PlayerController.h>
#include <PDaI_Project/HnS_Character.h>
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AHnS_WAbility::AHnS_WAbility()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	W_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(W_FX);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(W_FX);
	//ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	//ProjectileMovement->ProjectileGravityScale = 0;

}

// Called when the game starts or when spawned
void AHnS_WAbility::BeginPlay()
{
	if (GetInstigator() != nullptr) pController = Cast<AHnS_PlayerController>(GetInstigator()->GetController());
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("W casted"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHnS_WAbility::BeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AHnS_WAbility::OnOverlapEnd);
	Super::BeginPlay();
	//CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_WAbility::BeginOverlap);
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Particle, GetActorLocation());
	FVector wActorLocation = GetActorLocation();
	//pController->cachedDest_attack;
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *(pController->cachedDest_attack.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *(pController->cachedDest_attack.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::SanitizeFloat(pController->HP));
	FRotator rotVector = UKismetMathLibrary::FindLookAtRotation(pController->cachedDest_attack, wActorLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *(rotVector).ToString());
	wDestVector = wActorLocation + GetActorForwardVector() * WDistance;
	SetActorLocation(wDestVector);
	/*
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_WAbility::setLocationAfterDelay);
	FTimerHandle mTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(mTimerHandle, Delegate, 1, false);
	*/
	//UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, Particle, Cast<AHnS_Character>(GetInstigator())->GetActorLocation());
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_WAbility::enableDamage);
	FTimerHandle eTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(eTimerHandle, Delegate, 1, false);

	FTimerDelegate duration_Delegate = FTimerDelegate::CreateUObject(this, &AHnS_WAbility::disableEffect);
	FTimerHandle dTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(dTimerHandle, duration_Delegate, duration, false);
}

void AHnS_WAbility::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (canDamage)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Overlap begin"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("W overlap"));
		prevFireTicks = fireTicks;
		AController* PlayerC = GetInstigator()->GetController(); //Instigator - Object which created the actor/event (player created bullet)



		if (AHnS_Character* const TargetPlayer = Cast<AHnS_Character>(OtherActor))
		{
			if (OtherActor != PlayerC->GetPawn() && !TargetPlayer->invulnerable)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, PlayerC->GetPawn()->GetFName().ToString());
				if (OtherActor->GetClass() != PlayerC->GetPawn()->GetClass())
				{
					FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_WAbility::fireDamage, OtherActor, PlayerC);
					GetWorld()->GetTimerManager().SetTimer(mTimerHandle, Delegate, damageInterval, true);
					TargetPlayer->enableOnFire(damageInterval * fireTicks);
				}
				//UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, PlayerC, this, DamageType);
				//Destroy();
			}
			/*
			if (AHnS_Character* tempCharacter = Cast<AHnS_Character>(OtherActor))
			{
				if (tempCharacter->HP <= 0)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, deathImpactParticles, GetActorLocation());
				}
			}
			*/
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("[W Ability] AActor to AHnS_Character cast failed"));
		}
	}
}

void AHnS_WAbility::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Overlap end"));
}

void AHnS_WAbility::setLocationAfterDelay()
{
	SetActorLocation(wDestVector);
}
// Called every frame
void AHnS_WAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHnS_WAbility::fireDamage(AActor* actorToDamage, AController* damageInstigator)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Timer test"));
	fireTicks = fireTicks - 1;
	UGameplayStatics::ApplyDamage(actorToDamage, BaseDamage, damageInstigator, this, DamageType);
	if (fireTicks <= 0)
	{
		fireTicks = prevFireTicks;
		GetWorldTimerManager().ClearTimer(mTimerHandle);
	}
}

void AHnS_WAbility::enableDamage()
{
	canDamage = true;
	float prevActorZLocation = GetActorLocation().Z;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 10000));
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, prevActorZLocation));
}

void AHnS_WAbility::disableEffect()
{
	Destroy();
}

