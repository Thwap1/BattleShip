// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBlock.h"
#include "GameFramework/Actor.h"
#include <vector>
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

	UFUNCTION() void OnClickRandom(int nro);
	

	AGameController();
	
protected:
	void CreateGrids();
	bool validateBoard(int nro);

	virtual void BeginPlay() override;
	int GameState;
	std::vector<int> shipsizes{ 5,4,3,3,2 }; // ship sizes on board
	AMyBlock* Board[2][100];
	
public:
	void BlockClick(int nro);
	void CreateBoard(int nro);
	void GameStateChange(int state);
	int shoot(int nro, int boardNro);
	virtual void Tick(float DeltaTime) override;
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
};
