// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Enemy.generated.h"


class UBoxComponent;
/**
 * 
 */
UCLASS()
class APRK_API AEnemy : public AMainCharacter
{
	GENERATED_BODY()
public:
	AEnemy();
	

protected:
	

private:
	void BeginPlay() override;

	
	
};
