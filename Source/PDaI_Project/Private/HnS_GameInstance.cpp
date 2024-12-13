// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_GameInstance.h"

void UHnS_GameInstance::AddScore(float value)
{
	score += value;
}

float UHnS_GameInstance::GetScore()
{
	return score;
}

void UHnS_GameInstance::ResetScore()
{
	score = 0;
}
