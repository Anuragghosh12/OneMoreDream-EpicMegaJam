#pragma once

#include "MainCharacterData.generated.h"

class AMainCharacter;
class UPaperFlipbook;

UENUM(BlueprintType)
enum class AnimationDirection:uint8
{
	Down,
	Up,
	Right,
	Left,
	DownRight,
	DownLeft,
	UpRight,
	UpLeft
};


USTRUCT(BlueprintType)
struct FMainCharacterFlipbooks
{
	GENERATED_BODY()

	//Idle
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleUp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleDownRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleDownLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleUpRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleUpLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> IdleLeft;

	//Walking
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkUp;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkDownRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkDownLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkUpRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkUpLeft;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkRight;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UPaperFlipbook> WalkLeft;
};