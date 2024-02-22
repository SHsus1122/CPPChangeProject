// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/AuthorizationPanel.h"
#include "UMG/MessageModal.h"
#include "Components/CircularThrobber.h"
#include "Components/Button.h"

void UAuthorizationPanel::StartLoading() const
{
	LoadingWidget.Get()->SetVisibility(ESlateVisibility::Visible);
}

void UAuthorizationPanel::StopLoading() const
{
	LoadingWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
}

void UAuthorizationPanel::ShowSuccessMessage() const
{
	SuccessMessageWidget.Get()->SetVisibility(ESlateVisibility::Visible);
}

void UAuthorizationPanel::HideSuccessMessage() const
{
	SuccessMessageWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
}

void UAuthorizationPanel::ShowFailMessage() const
{
	FailMessageWidget.Get()->SetVisibility(ESlateVisibility::Visible);
}

void UAuthorizationPanel::HideFailMessage() const
{
	FailMessageWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
}

void UAuthorizationPanel::NativePreConstruct()
{
	UUserWidget::NativePreConstruct();
	
	if (IsValid(LoadingWidget))
	{
		LoadingWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (IsValid(SuccessMessageWidget))
	{
		SuccessMessageWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
		SuccessMessageWidget->OnCloseModalRequest.AddDynamic(this, &UAuthorizationPanel::BindCloseSuccessMessage);
	}
	if (IsValid(FailMessageWidget))
	{
		FailMessageWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
		FailMessageWidget->OnCloseModalRequest.AddDynamic(this, &UAuthorizationPanel::BindCloseFailMessage);
	}
	if (IsValid(ConfirmButton))
	{
		ConfirmButton->OnClicked.AddDynamic(this, &UAuthorizationPanel::BindConfirmClicked);
	}
}
