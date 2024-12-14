#include "HnS_Bullet.h"
#include "HnS_Character.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Hns_CharacterPlayer.h"
#include "HnS_BaseEnemy.h"

// Sets default values
AHnS_Bullet::AHnS_Bullet()
{
	BulletFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effects"));
	SetRootComponent(BulletFX);
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(BulletFX);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->ProjectileGravityScale = 0;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ProjectileMovement);

	PrimaryActorTick.bCanEverTick = true;

	//UPROPERTY(EditDefaultsOnly)

}

// Called when the game starts or when spawned
void AHnS_Bullet::BeginPlay()
{
	Super::BeginPlay();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Bullet Beginplay"));
	if (GetInstigator()) {
		ePlayerCharacter = Cast<AHnS_Character>(GetInstigator());
		PlayerC = GetInstigator()->GetController(); //Instigator - Object which created the actor/event (player created bullet)
	}
	else
	{
		ePlayerCharacter = nullptr;
		PlayerC = nullptr;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Instigator nullptr"));
	}
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_Bullet::BeginOverlap);
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Bullet::bulletDestroy, true);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, timeToDestroy, false);
	ignoredActors.Add(ePlayerCharacter);
}

void AHnS_Bullet::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OtherActor->GetFName().ToString());
	//OtherActor->GetFName().ToString() != "BP_HnS_PlayerChar_C_0"
	//GetOwner()->GetFName().ToString();
	if (GetOwner() == nullptr)
	{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Owner nullptr"));
	}
	if (GetInstigator() == nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Instigator nullptr"));
	}



	if (AHnS_Character* const TargetPlayer = Cast<AHnS_Character>(OtherActor))
	{
		if (OtherActor != PlayerC->GetPawn() && !TargetPlayer->invulnerable) 
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetFName().ToString());
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, impactParticles, GetActorLocation());
			//BulletHit();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, PlayerC->GetPawn()->GetFName().ToString());
			//if (OtherActor->GetClass() != PlayerC->GetPawn()->GetClass()) 
			//UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, PlayerC, this, DamageType);

			if (auto* tempCaster = Cast<AHns_CharacterPlayer>(GetInstigator()))
			{
				if (auto* tempTarget = Cast<AHnS_BaseEnemy>(OtherActor))
				{
					BulletHit(OtherActor);
				}
			}
			else
			{
				if (auto* tempTarget = Cast<AHns_CharacterPlayer>(OtherActor))
				{
					BulletHit(OtherActor);
				}
			}
			if (AHnS_Character* tempCharacter = Cast<AHnS_Character>(OtherActor))
			{
				if (tempCharacter->HP <= 0)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, deathImpactParticles, GetActorLocation());
				}
			}

			
		}

		
		
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("AActor to AHnS_Character cast failed"));
	}
}

void AHnS_Bullet::BulletHit(AActor* OtherActor)
{
	if (ePlayerCharacter->RCasted)
	{
		UGameplayStatics::ApplyRadialDamage(GetWorld(),
			BaseDamage,
			GetActorLocation(),
			radius,
			DamageType,
			ignoredActors,
			PlayerC,
			nullptr,
			false,
			ECollisionChannel::ECC_Visibility);
	}
	else
	{ 
		UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, GetInstigatorController(), this, DamageType);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Bullet Hit"));
	Destroy();
}

void AHnS_Bullet::bulletDestroy(bool Value)
{
	Destroy();
}

// Called every frame
void AHnS_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(this->GetActorLocation().ToString()));
	//reportnoise
}

