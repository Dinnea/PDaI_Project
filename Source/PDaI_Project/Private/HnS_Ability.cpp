// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_Ability.h"

// Sets default values
AHnS_Ability::AHnS_Ability()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHnS_Ability::SetReady(bool value)
{
	ready = value;
	GetWorld()->GetTimerManager().ClearTimer(cooldownHandle);
}

void AHnS_Ability::SetUser(AHnS_Character* pUser)
{
	user = pUser;
}

float AHnS_Ability::GetTimer()
{	
	return GetWorldTimerManager().GetTimerElapsed(cooldownHandle);
}

UTexture2D* AHnS_Ability::GetIcon()
{
	if (icon != nullptr) return icon;
	else return nullptr;
}


bool AHnS_Ability::Execute(bool flag)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Ability execute"));
	if (!ready) 
	{ 
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No execute."));
		return false; 
	}

	SetReady(false);
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_Ability::SetReady, true);
	GetWorld()->GetTimerManager().SetTimer(cooldownHandle, Delegate, cooldown, false);

	//GetWorldTimerManager().GetTimerElapsed(handle);
	return true;
}

bool AHnS_Ability::ExecuteRSubclass()
{
	return AHnS_Ability::Execute(false);
}

// Called when the game starts or when spawned
void AHnS_Ability::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHnS_Ability::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

