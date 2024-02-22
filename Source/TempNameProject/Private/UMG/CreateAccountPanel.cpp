// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/CreateAccountPanel.h"
#include "UMG/LabeledInput.h"
#include "Components/Button.h"
#include "UMG/MessageModal.h"


void UCreateAccountPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (IsValid(BackButton))
	{
		BackButton->OnClicked.AddDynamic(this, &UCreateAccountPanel::BindBackButtonClicked);
	}
}

void UCreateAccountPanel::BindConfirmClicked()
{
	const FText ID = IdWidget->GetValue();
	const FText Password = PasswordWidget->GetValue();
	const FText Nickname = NicknameWidget->GetValue();

	OnCreateAccountRequested.Broadcast(ID, Password, Nickname);
}

void UCreateAccountPanel::BindCloseSuccessMessage()
{
	OnOpenLoginPanelRequested.Broadcast();
}

void UCreateAccountPanel::BindCloseFailMessage()
{
	FailMessageWidget.Get()->SetVisibility(ESlateVisibility::Collapsed);
}

void UCreateAccountPanel::BindBackButtonClicked()
{
	OnOpenLoginPanelRequested.Broadcast();
}
