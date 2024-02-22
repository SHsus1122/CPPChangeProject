// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryUserWidget.h"

void UEntryUserWidget::NativeConstruct()
{
}

UUserWidget* UEntryUserWidget::GetEntrySoundWidget()
{
	return EntrySoundWidget;
}

bool UEntryUserWidget::EntrySoundISVisible()
{
	return EntrySoundWidget->IsVisible();
}

void UEntryUserWidget::ToggleVisibleWidget()
{
	if (EntrySoundISVisible())
	{
		EntrySoundWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		EntrySoundWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
