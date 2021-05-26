// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS(config = Game)
class BATTLESHIP_API AMyPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:
	
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	// Called when the game starts or when spawned

	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End, bool mousedown);
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class AMyBlock* CurrentBlockFocus;

};
