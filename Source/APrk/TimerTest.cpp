// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextRenderComponent.h"
#include "TimerTest.h"

// Sets default values
ATimerTest::ATimerTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CountDownText=CreateDefaultSubobject<UTextRenderComponent>(TEXT("Count-Down Text"));
	CountDownText->SetHorizontalAlignment(EHTA_Center);
	CountDownText->SetWorldSize(150.f);
	RootComponent=CountDownText;
	CountDownTime=3;

}

// Called when the game starts or when spawned
void ATimerTest::BeginPlay()
{
	Super::BeginPlay();
	UpdateDisplay();
	GetWorldTimerManager().SetTimer(CountDownTimerHandle,this, &ATimerTest::AdvanceTimer, 1.0f, true);
	
}

// Called every frame
void ATimerTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerTest::UpdateDisplay()
{
	FText CountDTempText = FText::FromString(FString::FromInt(FMath::Max(CountDownTime, 0)));
	CountDownText->SetText(CountDTempText);
}

void ATimerTest::AdvanceTimer()
{
	--CountDownTime;
	UpdateDisplay();
	if(CountDownTime<1)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		CountDownFinish();
	}	
}

void ATimerTest::CountDownFinish()
{
	FText CountdownFinishedText = FText::FromString(TEXT("GO!"));
	CountDownText->SetText(CountdownFinishedText);
}

