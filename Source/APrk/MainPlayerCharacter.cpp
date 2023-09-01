// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMainPlayerCharacter::AMainPlayerCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation=true;
	GetCharacterMovement()->bOrientRotationToMovement=false;
	bUseControllerRotationYaw=false;

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength=1500.f;
	SpringArm->SetRelativeRotation(FRotator(-20.f,0.f,0.f));
	SpringArm->TargetOffset=FVector(0.f,0.f,200.f);
	SpringArm->bDoCollisionTest=false;
	SpringArm->bInheritPitch=true ;
	SpringArm->bInheritRoll=false;
	SpringArm->bInheritYaw=true;
	SpringArm->bEnableCameraLag=false;
	SpringArm->bEnableCameraRotationLag=false;
	SpringArm->CameraLagSpeed=4.f;
	SpringArm->CameraLagMaxDistance=600.f;

	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView=55.f;
	// Camera->PostProcessBlendWeight=1.f;
	// Camera->PostProcessSettings.bOverride_DepthOfFieldFstop=true;
	// Camera->PostProcessSettings.DepthOfFieldFstop=0.5f;
	// Camera->PostProcessSettings.bOverride_DepthOfFieldSensorWidth=true;
	// Camera->PostProcessSettings.DepthOfFieldSensorWidth=100.f;
	// Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance=true;
	// Camera->PostProcessSettings.DepthOfFieldFocalDistance=SpringArm->TargetArmLength;
	// Camera->PostProcessSettings.bOverride_DepthOfFieldMinFstop=true;
	// Camera->PostProcessSettings.DepthOfFieldMinFstop=0.f;
	// Camera->PostProcessSettings.MotionBlurAmount=0.f;
	FootStepCoolDown=0.2f;
	PlaybackRate=0.8f;


	
}

void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FootstepTimerHandle,this,&AMainPlayerCharacter::OnFootStepTimeExpired, FootStepCoolDown,true);
}

void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Up"), this, &AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"),this, &AMainPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed ,this, &ACharacter::Jump);

	
	
}

void AMainPlayerCharacter::SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo> ViewInfo)
{
	Super::SetCurrentAnimationDirection(Velocity, ViewInfo);
	FVector Forward;
	FVector Right;
	if (ViewInfo.IsSet())
	{
		Forward = UKismetMathLibrary::GetForwardVector(ViewInfo.GetValue().Rotation);
		Right = UKismetMathLibrary::GetRightVector(ViewInfo.GetValue().Rotation);
	}
	else
	{
		Forward = GetActorForwardVector().GetSafeNormal();
		Right = GetActorRightVector().GetSafeNormal();
	}
	const float ForwardSpeed=FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(),Forward)*100)/100;
	const float RightSpeed=FMath::Floor(FVector::DotProduct(Velocity.GetSafeNormal(),Right)*100)/100;
	
	UE_LOG(LogTemp,Warning,TEXT("Forward %f, Right %f"), ForwardSpeed,RightSpeed);

	bIsMoving=ForwardSpeed!=0.0f || RightSpeed!=0.0f;
	
	if(bIsMoving)
	{
		if(ForwardSpeed > 0.0f && abs(RightSpeed) < 0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::Up;
		}
		else if(ForwardSpeed < -0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::DownRight;
		}
		else if(ForwardSpeed < -0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::DownLeft;
		}
		else if(ForwardSpeed < 0.5f && abs(RightSpeed) <= 0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::Down;
		}
		else if(ForwardSpeed > 0.5f && RightSpeed >= 0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::UpRight;
		}
		else if(ForwardSpeed > 0.5f && RightSpeed <= -0.5f)
		{
			CurrentAnimationDirection=AnimationDirection::UpLeft;
		}
		else if(abs(ForwardSpeed) < 0.5f && RightSpeed > 0.0f)
		{
			CurrentAnimationDirection=AnimationDirection::Right;
		}
		else
		{
			CurrentAnimationDirection=AnimationDirection::Left;
		}
	}
	if(bIsMoving && FootSteps!=NULL && !bFootStepPlaying && Velocity.Z==0.0f)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FootSteps, GetActorLocation(),FRotator::ZeroRotator, 1.0f, PlaybackRate);
		bFootStepPlaying = true;
		
		GetWorldTimerManager().SetTimer(FootstepTimerHandle, this, &AMainPlayerCharacter::OnFootStepTimeExpired, FootStepCoolDown, false);
	}
}
void AMainPlayerCharacter::OnFootStepTimeExpired()
{
	bFootStepPlaying = false;
}



void AMainPlayerCharacter::MoveForward(float Value)
{
	if(Value!=0.0f)
	{
		const FVector Direction=Camera->GetForwardVector();
		AddMovementInput(Direction, Value);
	}
}

void AMainPlayerCharacter::MoveRight(float Value)
{
	if(Value!=0.0f)
	{
		const FVector Direction=Camera->GetRightVector();
		AddMovementInput(Direction,Value);
	}
}
