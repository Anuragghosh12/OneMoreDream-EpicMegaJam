// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MainCharacterData.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class APRK_API AMainCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	


private:
	


protected:
	virtual void BeginPlay() override;

	
	UFUNCTION(BlueprintCallable,Category="BaseCharacter|Animate")
	void Animate(float DeltaTime,FVector OldLocation,const FVector OldVelocity);
	
	virtual void SetCurrentAnimationDirection(const FVector &Velocity, TOptional<FMinimalViewInfo>ViewInfo);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="BaseCharacter|Config")
	uint8 bIsMoving:1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseCharacter|Config")
	AnimationDirection CurrentAnimationDirection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="BaseCharacter|Config")
	FMainCharacterFlipbooks Flipbooks;
	
	
};
