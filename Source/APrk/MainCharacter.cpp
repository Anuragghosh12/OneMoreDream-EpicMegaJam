// Fill out your copyright notice in the Description page of Project Settings.
#include "MainCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMainCharacter::AMainCharacter()
{
	OnCharacterMovementUpdated.AddDynamic(this, &AMainCharacter::Animate);

	bReplicates=true;

	GetCapsuleComponent()->SetCapsuleRadius(70.f);

	GetSprite()->SetRelativeScale3D(FVector(11.f,11.f,11.f));
	GetSprite()->SetUsingAbsoluteRotation(true);
	GetSprite()->SetFlipbook(Flipbooks.IdleDown);
	GetSprite()->CastShadow=true;
}


void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
}

void AMainCharacter::Animate(float DeltaTime, FVector OldLocation, const FVector OldVelocity)
{
	TOptional<FMinimalViewInfo> ViewInfo;
	if(!IsPlayerControlled())
	{
		UWorld* World=GetWorld();
		if(World)
		{
			APlayerController* PlayerController=World->GetFirstPlayerController();
			if(PlayerController)
			{
				ACharacter* Character=PlayerController->GetCharacter();
				if(Character)
				{
					Character->CalcCamera(DeltaTime,ViewInfo.Emplace());
				}
			}
		}
	}
	SetCurrentAnimationDirection(OldVelocity,ViewInfo);
	if(OldVelocity.Size()>0.0f)
	{
		switch(CurrentAnimationDirection)
		{
		case AnimationDirection::Down:
			GetSprite()->SetFlipbook(Flipbooks.WalkDown);
			break;
		case AnimationDirection::Up:
			GetSprite()->SetFlipbook(Flipbooks.WalkUp);
			break;
		case AnimationDirection::Right:
			GetSprite()->SetFlipbook(Flipbooks.WalkRight);
			break;
		case AnimationDirection::Left:
			GetSprite()->SetFlipbook(Flipbooks.WalkLeft);
			break;
		case AnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(Flipbooks.WalkDownLeft);
			break;
		case AnimationDirection::DownRight:
			GetSprite()->SetFlipbook(Flipbooks.WalkDownRight);
			break;
		case AnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(Flipbooks.WalkUpLeft);
			break;
		case AnimationDirection::UpRight:
			GetSprite()->SetFlipbook(Flipbooks.WalkUpRight);
			break;
		default:
				break;
		}
	}
	else
	{
		switch(CurrentAnimationDirection)
		{
		case AnimationDirection::Down:
			GetSprite()->SetFlipbook(Flipbooks.IdleDown);
			break;
		case AnimationDirection::Up:
			GetSprite()->SetFlipbook(Flipbooks.IdleUp);
			break;
		case AnimationDirection::Right:
			GetSprite()->SetFlipbook(Flipbooks.IdleRight);
			break;
		case AnimationDirection::Left:
			GetSprite()->SetFlipbook(Flipbooks.IdleLeft);
			break;
		case AnimationDirection::DownLeft:
			GetSprite()->SetFlipbook(Flipbooks.IdleDownLeft);
			break;
		case AnimationDirection::DownRight:
			GetSprite()->SetFlipbook(Flipbooks.IdleDownRight);
			break;
		case AnimationDirection::UpLeft:
			GetSprite()->SetFlipbook(Flipbooks.IdleUpLeft);
			break;
		case AnimationDirection::UpRight:
			GetSprite()->SetFlipbook(Flipbooks.IdleUpRight);
			break;
		default:
			break;
		}
	}
}

void AMainCharacter::SetCurrentAnimationDirection(const FVector& Velocity, TOptional<FMinimalViewInfo>ViewInfo)
{
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

	UE_LOG(LogTemp,Warning,TEXT("Forward %f, Right %f"),ForwardSpeed,RightSpeed);
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
	
}

