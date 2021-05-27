// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUIWidget.h"
#include "Components/Button.h"
#include "GameController.h"
#include "Engine.h"

UMyUIWidget::UMyUIWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMyUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	
	
	if(!RandomizeField -> OnClicked.IsBound()) RandomizeField -> OnClicked.AddDynamic(this, &UMyUIWidget::OnClickRandom);
	SetGameState(0);
}



void UMyUIWidget::OnClickRandom() {
	
	if (GC)GC->OnClickRandom(1);
}
void UMyUIWidget::SetGameState(int state) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Screen Message"));
	switch (state) {
	case 0:
		RandomizeField->SetVisibility(ESlateVisibility::Visible);
		Begin1->SetVisibility(ESlateVisibility::Hidden);
		Begin2->SetVisibility(ESlateVisibility::Hidden);
		break;
	case 1:
		RandomizeField->SetVisibility(ESlateVisibility::Visible);
		Begin1->SetVisibility(ESlateVisibility::Visible);
		Begin2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2: case 3:
		RandomizeField->SetVisibility(ESlateVisibility::Hidden);
		Begin1->SetVisibility(ESlateVisibility::Hidden);
		Begin2->SetVisibility(ESlateVisibility::Hidden);
		break;
	}
}