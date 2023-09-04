// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "TimerTest.generated.h"



UCLASS()
class APRK_API ATimerTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int32 CountDownTime;
	UTextRenderComponent* CountDownText;
	void UpdateDisplay();

	void AdvanceTimer();
	void CountDownFinish();
	FTimerHandle CountDownTimerHandle;


	

};
