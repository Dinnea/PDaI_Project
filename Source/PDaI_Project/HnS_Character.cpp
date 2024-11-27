// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Character.h"
#include "HnS_Weapon.h"
#include "HnS_Bullet.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthBarWidget.h"

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

// Sets default values
AHnS_Character::AHnS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetupMovement();
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
	Weapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(),TEXT("WeaponSocket"));
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
		weaponPtr->SetPlayerPointer(this);
		weaponPtr->SetProjectileSpawnLocation(SpawnLocation);
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

}

// Called to bind functionality to input
void AHnS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

USceneComponent* AHnS_Character::GetProjectileSpawnLocation()
{
	return SpawnLocation;
}

AActor* AHnS_Character::AutoAttack()
{
	//FActorSpawnParameters SpawnParams;
	//SpawnParams.Instigator = this;
	//SpawnParams.Owner = this;
	//AActor* SpawnedActor = GetWorld()->SpawnActor<AHnS_Bullet>(BulletToSpawn,SpawnLocation->GetComponentLocation() + FVector(0, 0, 0) , GetActorRotation(), SpawnParams);

	if (AHnS_Weapon* weaponPtr = Cast<AHnS_Weapon>(Weapon->GetChildActor())) return weaponPtr->Attack();

	return nullptr;
}

