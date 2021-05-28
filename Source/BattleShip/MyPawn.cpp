// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "MyBlock.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values

AMyPawn::AMyPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{

		FVector Start, Dir, End;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		bool mousedown = false;
		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
			mousedown = PC->IsInputKeyDown("LeftMouseButton");
		}


		End = Start + (Dir * 8000.0f);
		TraceForBlock(Start, End, mousedown);

	}
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("TriggerClick", EInputEvent::IE_Pressed, this, &AMyPawn::TriggerClick);

}

void AMyPawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	int maxsize = ((((int)Result[0]) >> 1) > (int)Result[1]) ? (int)Result[1] : ((int)Result[0]) >> 1;
	/* */
	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
	OutResult.Location = FVector(0.0f, 0.0f, 1100000/maxsize);
}


void AMyPawn::TriggerClick()
{

	if (CurrentBlockFocus)
	{
		CurrentBlockFocus->HandleClicked();
	}
}

void AMyPawn::TraceForBlock(const FVector& Start, const FVector& End, bool mousedown)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (HitResult.Actor.IsValid())
	{
		AMyBlock* HitBlock = Cast<AMyBlock>(HitResult.Actor.Get());
		if (CurrentBlockFocus != HitBlock)
		{
			if (CurrentBlockFocus)
			{
				CurrentBlockFocus->Highlight(false);
			}
			if (HitBlock)
			{
				HitBlock->Highlight(mousedown);

			}
			CurrentBlockFocus = HitBlock;
		}
	}
	else if (CurrentBlockFocus)
	{
		CurrentBlockFocus->Highlight(false);
		CurrentBlockFocus = nullptr;
	}
}

