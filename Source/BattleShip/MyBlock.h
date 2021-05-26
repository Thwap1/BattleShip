// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBlock.generated.h"

UCLASS()
class BATTLESHIP_API AMyBlock : public AActor
{
	GENERATED_BODY()

		UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))	/** Dummy root component */
		class USceneComponent* DummyRoot;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))/** StaticMesh component for the clickable block */
		class UStaticMeshComponent* BlockMesh;
public:
	AMyBlock();

	UPROPERTY()
		class UMaterial* WhiteMaterial;
	UPROPERTY()
		class UMaterialInstance* BlueMaterial;
	UPROPERTY()
		class UMaterialInstance* RedMaterial;
	UPROPERTY()
		class AGameController* GC;

	UFUNCTION()
		void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	UFUNCTION()
		void OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	void HandleClicked();

	void Highlight(bool bOn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	int gridvalue = 1;
	void SetMaterial(int matcolor);
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }/** Returns DummyRoot subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }/** Returns BlockMesh subobject **/

};
