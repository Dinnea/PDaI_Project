// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_EAbility.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
//#include <PDaI_Project/HnS_Weapon.h>
#include <PDaI_Project/HnS_Character.h>

// Sets default values
AHnS_EAbility::AHnS_EAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	E_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(E_FX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(E_FX);
	trapMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	trapMesh->SetupAttachment(E_FX);
	trapMesh->Mobility = EComponentMobility::Movable;
	//trapMesh->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	explosionSound = CreateDefaultSubobject<USoundBase>(TEXT("Explosion sound"));

}

// Called when the game starts or when spawned
void AHnS_EAbility::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("E ability casted"));
	Super::BeginPlay();

	ePlayerCharacter = Cast<AHnS_Character>(GetInstigator());
	ePlayerCharacter->setCrouch(true);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_EAbility::BeginOverlap);

	ignoredActors.Add(ePlayerCharacter);

	trapMesh->ToggleVisibility();

	/*
	if ((eWeapon = Cast<AHnS_Weapon>(GetInstigator())))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Cast succesfull"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Cast failed"));
	}
	*/

	FTimerDelegate cDelegate = FTimerDelegate::CreateUObject(this, &AHnS_EAbility::disableCrouch);
	FTimerHandle cTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(cTimerHandle, cDelegate, 0.8, false);
	
}

void AHnS_EAbility::disableCrouch()
{
	ePlayerCharacter->setCrouch(false);
	trapMesh->ToggleVisibility();
	trap_active_particle = UGameplayStatics::SpawnEmitterAtLocation(this, E_aura, FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - zOffset));
}

void AHnS_EAbility::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AController* PlayerC = GetInstigator()->GetController();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Entered E overlap");

	if (AHnS_Character* const TargetPlayer = Cast<AHnS_Character>(OtherActor))
	{
		if (OtherActor != PlayerC->GetPawn() && !TargetPlayer->invulnerable)
		{
			AHnS_Character* otherPlayer = Cast<AHnS_Character>(OtherActor);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, PlayerC->GetPawn()->GetFName().ToString());
			if (OtherActor->GetClass() != PlayerC->GetPawn()->GetClass())
			{
				otherPlayer->immobilized = true;
				FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_EAbility::despawn, otherPlayer);
				FTimerHandle dTimerHandle;
				GetWorld()->GetTimerManager().SetTimer(dTimerHandle, Delegate, effect_duration, false);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, "E debug test");
				UGameplayStatics::ApplyRadialDamage(GetWorld(),
					baseDamage,
					GetActorLocation(),
					radius,
					DamageType,
					ignoredActors,
					PlayerC,
					nullptr,
					false,
					ECollisionChannel::ECC_Visibility);
				otherPlayer->GetCharacterMovement()->DisableMovement();
				trapMesh->ToggleVisibility();
				UGameplayStatics::SpawnEmitterAtLocation(this, E_activate, FVector(otherPlayer->GetActorLocation().X, otherPlayer->GetActorLocation().Y, otherPlayer->GetActorLocation().Z - zOffset));
				trap_active_particle->Deactivate();
				immobility_effect = UGameplayStatics::SpawnEmitterAtLocation(this, E_ImmobilityEffect, FVector(otherPlayer->GetActorLocation().X, otherPlayer->GetActorLocation().Y, otherPlayer->GetActorLocation().Z));
				UGameplayStatics::PlaySound2D(GetWorld(), explosionSound, 1, 1, 0, NULL, nullptr, true);
				CollisionSphere->OnComponentBeginOverlap.RemoveAll(this);
					//UGameplayStatics::ApplyDamage(actorToDamage, BaseDamage, damageInstigator, this, DamageType);
			}
		}
	}
}

void AHnS_EAbility::despawn(AHnS_Character* targetPlayer)
{
	FTimerDelegate Delegate1 = FTimerDelegate::CreateUObject(this, &AHnS_EAbility::despawn_delay, targetPlayer);
	FTimerHandle deTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(deTimerHandle, Delegate1, 1, false);
	targetPlayer->immobilized = false;
	immobility_effect->Deactivate();
}

void AHnS_EAbility::despawn_delay(AHnS_Character* targetPlayer)
{
	targetPlayer->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	Destroy();
}

// Called every frame
void AHnS_EAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, ePlayerCharacter->trap_crouch ? TEXT("Crouch: true") : TEXT("Crouch: false"));

}

