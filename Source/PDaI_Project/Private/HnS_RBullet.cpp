// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_RBullet.h"
#include "Kismet/GameplayStatics.h"

AHnS_RBullet::AHnS_RBullet()
{
	//AHnS_Bullet::AHnS_Bullet();
	ultimate_arrowSound = CreateDefaultSubobject<USoundBase>(TEXT("Ult arrow sound"));
}

void AHnS_RBullet::BeginPlay()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, TEXT("R Bullet Beginplay"));
	UGameplayStatics::PlaySound2D(GetWorld(), ultimate_arrowSound, 1, 1, 0, NULL, nullptr, true);
	Super::BeginPlay();
}

void AHnS_RBullet::BeginOverlap(UPrimitiveComponent* OverlappedContent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BeginOverlap(OverlappedContent,OtherActor,OtherComp,OtherBodyIndex,bFromSweep,SweepResult);
}

void AHnS_RBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
