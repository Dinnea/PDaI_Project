// Fill out your copyright notice in the Description page of Project Settings.


#include "HealArea.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include <PDaI_Project/HnS_CharacterPlayer.h>
#include <PDaI_Project/HnS_PlayerController.h>

// Sets default values
AHealArea::AHealArea()
{
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	SetRootComponent(CollisionSphere);

	greenFlare1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Green flares particle 1"));
	greenFlare1->SetupAttachment(RootComponent);
	greenFlare2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Green flares particle 2"));
	greenFlare2->SetupAttachment(RootComponent);
	greenFlare3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Green flares particle 3"));
	greenFlare3->SetupAttachment(RootComponent);
	greenFlare4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Green flares particle 4"));
	greenFlare4->SetupAttachment(RootComponent);

	redFlare1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Red flares particle 1"));
	redFlare1->SetupAttachment(RootComponent);
	redFlare2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Red flares particle 2"));
	redFlare2->SetupAttachment(RootComponent);
	redFlare3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Red flares particle 3"));
	redFlare3->SetupAttachment(RootComponent);
	redFlare4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Red flares particle 4"));
	redFlare4->SetupAttachment(RootComponent);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealArea::BeginPlay()
{
	Super::BeginPlay();
	flare_toggleVisibility(false); //red off
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealArea::BeginOverlap);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AHealArea::OnOverlapEnd);
	if (GetInstigator()) {
		controlled_player = Cast<AHnS_Character>(GetInstigator());
		PlayerC = Cast<AHnS_PlayerController>(GetInstigator()->GetController());
	}

	FTimerDelegate delay_Delegate = FTimerDelegate::CreateUObject(this, &AHealArea::overlapReset);
	FTimerHandle delay_TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(delay_TimerHandle, delay_Delegate, 0.5, false);
}

void AHealArea::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (controlled_player == Cast<AHnS_Character>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Overlap begin"));
		controlled_player->invulnerable = true;
		PlayerC->setCanUseAbilities(false);
		if ((controlled_player->HP < controlled_player->MaxHP) && canUseAura && initialUseAmount)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("HealAura overlap"));
			canHeal = true;
			canUseAura = false;
			initialUseAmount -= 1;
			prevTickAmount = ticksAmount;
			FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHealArea::heal);
			GetWorld()->GetTimerManager().SetTimer(hTimerHandle, Delegate, healInterval, true);
			controlled_player->toggleOnHeal(); //player heal particle on

			FTimerDelegate aDelegate = FTimerDelegate::CreateUObject(this, &AHealArea::aura_cooldown);
			FTimerHandle aTimerHandle;
			GetWorld()->GetTimerManager().SetTimer(aTimerHandle, aDelegate, auraActivationCooldown, false);
		}

	}
}

void AHealArea::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, *(OtherActor->GetFName()).ToString());
	if (controlled_player == Cast<AHnS_Character>(OtherActor))
	{
		canHeal = false;
		controlled_player->invulnerable = false;
		PlayerC->setCanUseAbilities(true);

		if (endOverlapCount == 2) //Player triggers end overlap on game start 2 times for some reason (idk why), so this fixes overlap not working by resetting it on 3rd time
		{
			overlapReset();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Overlap reset"));
		}
		endOverlapCount++;
	}
}

void AHealArea::heal()
{
	ticksAmount = ticksAmount - 1;
	if (controlled_player && canHeal)
	{
		if(controlled_player->HP < controlled_player->MaxHP) controlled_player->HP += healPerTick;
	}
	if (ticksAmount <= 0)
	{
		flare_toggleVisibility(true); //green off
		flare_toggleVisibility(false); //red on
		controlled_player->toggleOnHeal(); //player heal particle off
		ticksAmount = prevTickAmount;
		GetWorldTimerManager().ClearTimer(hTimerHandle);
	}
}

void AHealArea::aura_cooldown()
{
	flare_toggleVisibility(false); //red off
	flare_toggleVisibility(true); //green on
	canUseAura = true;
	overlapReset();
}

void AHealArea::flare_toggleVisibility(bool color)
{
	if (color)
	{
		greenFlare1->ToggleVisibility();
		greenFlare2->ToggleVisibility();
		greenFlare3->ToggleVisibility();
		greenFlare4->ToggleVisibility();
	}
	else
	{
		redFlare1->ToggleVisibility();
		redFlare2->ToggleVisibility();
		redFlare3->ToggleVisibility();
		redFlare4->ToggleVisibility();
	}
}

void AHealArea::overlapReset()
{
	float prevActorZLocation = GetActorLocation().Z;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 10000));
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, prevActorZLocation));
}

// Called every frame
void AHealArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, controlled_player->invulnerable ? TEXT("Invulnerable") : TEXT("Vulnerable"));

}

