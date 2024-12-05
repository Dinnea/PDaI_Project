// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Character.h"
#include "HnS_Weapon.h"
#include "HnS_Bullet.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthBarWidget.h"
#include <HnS_Ability.h>
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <TestChildAbility.h>

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

void AHnS_Character::enableMovement()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Enable movement"));
	GetCharacterMovement()->SetMovementMode(MOVE_NavWalking);
}

void AHnS_Character::onFire()
{
	//FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Character::applyFireDamage);
	//GetWorld()->GetTimerManager().SetTimer(fTimerHandle, Delegate, damageInterval, false, 1.f);
}

void AHnS_Character::updateRoll()
{
	playRollAnimation = false;
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

void AHnS_Character::SetupHPBar()
{
    springArm1 = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm 1"));
	springArm1->SetupAttachment(RootComponent);
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue"));
	if (WidgetComponent)
	{
		WidgetComponent->SetupAttachment(springArm1, TEXT("Spring Arm"));
		springArm1->bUsePawnControlRotation = false;
		springArm1->TargetArmLength = 10.f;
		springArm1->SetUsingAbsoluteRotation(true);
		//WidgetComponent->SetAbsolute(false, false, false);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
		WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 125.f)); //Attach healthbar (from widget) above players/enemies head
		WidgetComponent->SetRelativeRotation(FRotator(180.f, 75.f, 180.f));
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/WBP_NPCHealthBar") }; //Choose blueprint to attach the healthbar from
		if (WidgetClass.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("WidgetClass succedeed"));
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
		}
	}
}

// Sets default values
AHnS_Character::AHnS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupMovement();
	SetupHPBar();

	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));

	abilityW = CreateDefaultSubobject<UChildActorComponent>(TEXT("AbilityW"));
	abilityW->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	abilityE = CreateDefaultSubobject<UChildActorComponent>(TEXT("AbilityE"));
	abilityE->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet spawn points"));
	SpawnLocation->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AHnS_Character::BeginPlay()
{
	Super::BeginPlay();
	/*check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using TestCharacter."));*/
	MaxHP = HP;
	if(auto* const weaponPtr = Cast<AHnS_Weapon>(Weapon->GetChildActor()))
	{
		weaponPtr->SetUser(this);
		weaponPtr->SetAbilitySpawnLocation(SpawnLocation);
	}

	if (auto* abilityPtr = Cast<AHnS_Weapon>(abilityW->GetChildActor())) 
	{
		abilityPtr->SetUser(this);
		abilityPtr->SetAbilitySpawnLocation(SpawnLocation);
	}

	if (auto* eAbilityPtr = Cast<AHnS_Weapon>(abilityE->GetChildActor()))
	{
		eAbilityPtr->SetUser(this);
		eAbilityPtr->SetAbilitySpawnLocation(SpawnLocation);
	}
}

// Called every frame
void AHnS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (auto const widget = Cast<UHealthBarWidget>(WidgetComponent->GetUserWidgetObject()))
	{
		widget->SetBarValuePercent(HP/MaxHP);
	}

	FVector v1 = GetActorLocation() + Distance;

	globalDeltaTime = DeltaTime;

	if (WaitTime > 0)
	{
		WaitTime = WaitTime - DeltaTime;
		return;
	}
	if (playRollAnimation)
	{
		SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), destVector, DeltaTime, InterpSpeed));
		//FVector(cachedDest_roll.X, cachedDest_roll.Y, Zpos)
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(GetActorRotation().Vector().ToString()));

}

// Called to bind functionality to input
void AHnS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



bool AHnS_Character::AutoAttack()
{
	if (auto* weaponPtr = Cast<AHnS_Ability>(Weapon->GetChildActor())) return weaponPtr->Execute();
	return false;
}

bool AHnS_Character::AbilityW()
{
	if (auto* abilityPtr = Cast<AHnS_Ability>(abilityW->GetChildActor())) return abilityPtr->Execute();
	return false;
}

float AHnS_Character::roll()
{
	invulnerable = true;
	FHitResult attackHit;
	bool attackHitSuccessful = false;

	FVector ActorLocation = GetActorLocation();

	attackHitSuccessful = Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, attackHit);

	if (attackHitSuccessful) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Debug test"));
		cachedDest_roll = attackHit.Location;
	}
	rotatePlayer(cachedDest_roll);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Roll debug"));
	}
	FRotator rotVector = UKismetMathLibrary::FindLookAtRotation(cachedDest_roll, ActorLocation);
	destVector = GetActorLocation() + GetActorForwardVector()*Distance;
	//destVector.X *= -1;
	//rotVector = rotVector * -1;
	playRollAnimation = true;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Roll debug"));
	return 0;
}

void AHnS_Character::rotatePlayer(FVector destination)
{
	FVector PlayerLoc = GetActorLocation();
	//FVector CursorLocation = cachedDest_attack;
	FRotator PlayerRotation = UKismetMathLibrary::FindLookAtRotation(destination, PlayerLoc);
	FRotator newPlayerRotation = FRotator(GetActorRotation().Pitch, PlayerRotation.Yaw - 180, GetActorRotation().Roll);
	SetActorRotation(newPlayerRotation); //ludek->GetActorRotation().Yaw
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *(PlayerRotation.ToString()));
}

bool AHnS_Character::AbilityE()
{
	if (!playRollAnimation)
	{
		if (auto* abilityPtr = Cast<AHnS_Ability>(abilityE->GetChildActor())) return abilityPtr->Execute();
	}
	return false;
}

void AHnS_Character::setCrouch(bool flag)
{
	trap_crouch = flag;
}

