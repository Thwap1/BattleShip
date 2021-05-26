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
	
}




void UMyUIWidget::OnClickRandom() {
	if (GC)GC->OnClickRandom(1);
}