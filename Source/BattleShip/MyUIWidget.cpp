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
	if(!StartButton -> OnClicked.IsBound()) StartButton->OnClicked.AddDynamic(this, &UMyUIWidget::OnClickBegin);
}


void UMyUIWidget::OnClickBegin() {
	
	if (GC)
		if (GC->OnClickBegin(1)) {
			RandomizeField->SetVisibility(ESlateVisibility::Hidden);
			StartButton->SetVisibility(ESlateVisibility::Hidden);
		}
}

void UMyUIWidget::OnClickRandom() {
	
	if (GC)GC->OnClickRandom(1);
}