// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_AoE.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHnS_AoE::AHnS_AoE()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	vfx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VFX"));
	SetRootComponent(vfx);

	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(vfx);

	

}

// Called when the game starts or when spawned
void AHnS_AoE::BeginPlay()
{
	Super::BeginPlay();
	vfx->SetNiagaraVariableFloat(FString("angle"), angle);
	vfx->SetNiagaraVariableFloat(FString("length"), range);
	vfx->SetNiagaraVariableFloat(FString("lifetime"), lifeTime-.5f);
	CollisionSphere->SetSphereRadius(range);

	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AHnS_AoE::OnTimeout);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, lifeTime, false);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHnS_AoE::BeginOverlap);
	
}

//find objects in collider-> find n

void AHnS_AoE::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, OtherActor->GetFName().ToString());
}

void AHnS_AoE::OnTimeout()
{
	this->Destroy();
}

// Called every frame
void AHnS_AoE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

