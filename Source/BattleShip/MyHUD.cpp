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
	if (MyUIWidget && t!=1 && t!=-1)
	{
		if (t < 0) { //loser bracket
			t += DeltaSeconds * (50 + -t * 4);
			if (t > -1) t = -1;
			MyUIWidget->WinLetterScale(t);
		}
		else {
			t -= DeltaSeconds * (50 + t * 4);
			if (t < 1) t = 1;
			MyUIWidget->WinLetterScale(t);
		}
	}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}
void AMyHUD::SetGameState(int state) {
	if (state == 10)t = 150;
	if (state == 11)t = -150;
	if (MyUIWidget)MyUIWidget->SetGameState(state);
}