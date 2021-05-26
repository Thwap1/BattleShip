// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"

AMyHUD::AMyHUD()
{

}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MyUIWidgetClass)
	{
		MyUIWidget = CreateWidget<UMyUIWidget>(GetWorld(), MyUIWidgetClass);

		if (MyUIWidget)
		{
			MyUIWidget->AddToViewport();
		}
	}
}

void AMyHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (MyUIWidget)
	{

	}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}