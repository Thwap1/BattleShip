// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Components/WidgetComponent.h"
#include "MyUIWidget.h"
#include "MyHUD.generated.h"

/**
 *
 */
UCLASS()
class BATTLESHIP_API AMyHUD : public AHUD
{
	GENERATED_BODY()


public:
	AMyHUD();


	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;


	UPROPERTY(EditAnywhere)
		class AGameController* GC;
	UPROPERTY(EditDefaultsOnly, Category = "Interactive")
		TSubclassOf<UUserWidget> MyUIWidgetClass;
	UFUNCTION()
		void SetGameState(int state);
	float t=150;

private:
	
	UMyUIWidget* MyUIWidget;
};