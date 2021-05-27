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
	if(!AgainButton->OnClicked.IsBound()) AgainButton->OnClicked.AddDynamic(this, &UMyUIWidget::OnClickAgain);
	SetGameState(0);
}

void UMyUIWidget::OnClickAgain() {

	if (GC)GC->OnClickAgain();
}
void UMyUIWidget::WinLetterScale(float f) {
	
	if (f > 0) {
		if (Win1) Win1->SetRenderScale(FVector2D(f, 1.0f));
		if (Win2) Win2->SetRenderScale(FVector2D(f, 1.0f));
		if (Win3) Win3->SetRenderScale(FVector2D(f, 1.0f));
	}
	else {
		if (lose1) lose1->SetRenderScale(FVector2D(-f,1.0f));
		if (lose2) lose2->SetRenderScale(FVector2D(-f,1.0f));
		if (lose3) lose3->SetRenderScale(FVector2D(-f,1.0f));
	}
	
	
}
void UMyUIWidget::OnClickRandom() {
	
	if (GC)GC->OnClickRandom(1);
}
void UMyUIWidget::SetGameState(int state) {
	
	Win1->SetVisibility(ESlateVisibility::Hidden);
	Win2->SetVisibility(ESlateVisibility::Hidden);
	Win3->SetVisibility(ESlateVisibility::Hidden);
	lose1->SetVisibility(ESlateVisibility::Hidden);
	lose2->SetVisibility(ESlateVisibility::Hidden);
	lose3->SetVisibility(ESlateVisibility::Hidden);
	Begin1->SetVisibility(ESlateVisibility::Hidden);
	Begin2->SetVisibility(ESlateVisibility::Hidden);
	ShadeImage->SetVisibility(ESlateVisibility::Hidden);
	AgainButton->SetVisibility(ESlateVisibility::Hidden);
	RandomizeField->SetVisibility(ESlateVisibility::Hidden);
	switch (state) {
	case 0:
		RandomizeField->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:
		RandomizeField->SetVisibility(ESlateVisibility::Visible);
		Begin1->SetVisibility(ESlateVisibility::Visible);
		Begin2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2: case 3:
		break;
	
	case 10:
		Win1->SetVisibility(ESlateVisibility::Visible);
		Win2->SetVisibility(ESlateVisibility::Visible);
		Win3->SetVisibility(ESlateVisibility::Visible);
		ShadeImage->SetVisibility(ESlateVisibility::Visible);
		AgainButton->SetVisibility(ESlateVisibility::Visible);
		break;
	case 11:
		AgainButton->SetVisibility(ESlateVisibility::Visible);
		ShadeImage->SetVisibility(ESlateVisibility::Visible);
		lose1->SetVisibility(ESlateVisibility::Visible);
		lose2->SetVisibility(ESlateVisibility::Visible);
		lose3->SetVisibility(ESlateVisibility::Visible);
		break;
	}
	
}