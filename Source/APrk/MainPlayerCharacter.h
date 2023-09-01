// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class APRK_API AMainPlayerCharacter : public AMainCharacter
{
	GENERATED_BODY()
public:
	AMainPlayerCharacter();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Animation|Sound")
	 class USoundBase* FootSteps;

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	 virtual void SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	void OnFootStepTimeExpired();
	UPROPERTY(EditAnywhere,Category="Animation|Sound")
	float PlaybackRate = 0.8f;
	
	bool bFootStepPlaying;
	UPROPERTY(EditAnywhere,Category="Animation|Sound")
	float FootStepCoolDown;
	FTimerHandle FootstepTimerHandle;

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"),Category="MainPlayer|Components")
	TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta=(AllowPrivateAccess="true"),Category="MainPlayer|Components")
	TObjectPtr<UCameraComponent> Camera;
	
};


