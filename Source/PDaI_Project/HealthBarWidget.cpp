// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"

/*
void UHealthBarWidget::NativeConstruct()
{
	UUserWidget::NativeConstruct();
}
*/

void UHealthBarWidget::SetBarValuePercent(float const value)
{
	HealthValue->SetPercent(value);
}

void UHealthBarWidget::SetEffectText(FText const value)
{
	if (NameTextBlock)
	{
		NameTextBlock->SetText(value);
	}
}
