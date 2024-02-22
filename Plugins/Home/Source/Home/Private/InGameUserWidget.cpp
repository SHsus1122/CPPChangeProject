// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUserWidget.h"

void UInGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

UUserWidget* UInGameUserWidget::GetInGameChatWidget()
{
	return InGameChatWidget;
}

UUserWidget* UInGameUserWidget::GetInGameSoundWidget()
{
	return InGameSoundWidget;
}

bool UInGameUserWidget::InGameSoundISVisible()
{
	return InGameSoundWidget->IsVisible();
}

void UInGameUserWidget::ToggleVisibleWidget()
{
	if (InGameSoundISVisible())
	{
		InGameSoundWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		InGameSoundWidget->SetVisibility(ESlateVisibility::Visible);
	}
}