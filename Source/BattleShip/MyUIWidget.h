// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"


#include "Runtime/UMG/Public/UMG.h"
#include "GameController.h"
#include "MyUIWidget.generated.h"

/**
 *
 */
UCLASS()
class BATTLESHIP_API UMyUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMyUIWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UButton* RandomizeField;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSoftObjectPtr<AGameController> GC;
	UFUNCTION() void OnClickRandom();


};