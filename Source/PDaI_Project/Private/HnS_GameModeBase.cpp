// Fill out your copyright notice in the Description page of Project Settings.


#include "HnS_GameModeBase.h"

void AHnS_GameModeBase::AddScore(float value)
{
	score += value;
}

float  AHnS_GameModeBase::GetScore()
{
	return score;
}

void AHnS_GameModeBase::ResetScore()
{
	score = 0;
}
