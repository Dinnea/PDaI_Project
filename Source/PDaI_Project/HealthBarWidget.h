// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PDAI_PROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//virtual void NativeConstruct() override;
	void SetBarValuePercent(float const value);
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HealthValue = nullptr;

	void SetEffectText(FText const value);
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* NameTextBlock = nullptr;
private:
};
