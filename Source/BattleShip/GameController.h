// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBlock.h"
#include "GameFramework/Actor.h"
#include "GameController.generated.h"

UCLASS()
class BATTLESHIP_API AGameController : public AActor
{
	GENERATED_BODY()
		UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))/** Dummy root component */
		class USceneComponent* DummyRoot;

public:

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		int32 Size;
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
		float BlockSpacing;
	AGameController();

protected:
	void CreateGrids();
	void validateBoard();
	void createBoard();
	virtual void BeginPlay() override;
	int GameState;
	int shipsizes[5] = { 5,4,3,3,2 }; // ship sizes on board
	AMyBlock* Board1[100];
	AMyBlock* Board2[100];
public:
	void BlockClick();
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
};
