#include "HnS_Bullet.h"
#include "HnS_Character.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_Bullet::BeginOverlap);
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Bullet::bulletDestroy, true);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, timeToDestroy, false);
}

void AHnS_Bullet::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OtherActor->GetFName().ToString());
	//OtherActor->GetFName().ToString() != "BP_HnS_PlayerChar_C_0"
	//GetOwner()->GetFName().ToString();
	if (GetOwner() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Owner nullptr"));
	}
	if (GetInstigator() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Instigator nullptr"));
	}
	AController* PlayerC = GetInstigator()->GetController(); //Instigator - Object which created the actor/event (player created bullet)



	if (AHnS_Character* const TargetPlayer = Cast<AHnS_Character>(OtherActor))
	{
		if (OtherActor != PlayerC->GetPawn() && !TargetPlayer->invulnerable) //(OtherActor->GetClass() != PlayerC->GetPawn()->GetClass() && !TargetPlayer->invulnerable)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, OtherActor->GetFName().ToString());
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, impactParticles, GetActorLocation());
			//BulletHit();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, PlayerC->GetPawn()->GetFName().ToString());
			UGameplayStatics::ApplyDamage(OtherActor, BaseDamage, PlayerC, this, DamageType);
			Destroy();
		}
		if (AHnS_Character* tempCharacter = Cast<AHnS_Character>(OtherActor))
		{
			if (tempCharacter->HP <= 0)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, deathImpactParticles, GetActorLocation());
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("AActor to AHnS_Character cast failed"));
	}
}

void AHnS_Bullet::BulletHit()
{
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
}

