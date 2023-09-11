// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

AMyAIController::AMyAIController()
{
	PrimaryActorTick.bCanEverTick=false;
}

void AMyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
