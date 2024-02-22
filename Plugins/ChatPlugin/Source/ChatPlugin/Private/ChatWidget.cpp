// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCountTextBox = Cast<UTextBlock>(GetWidgetFromName("PlayerCountTextBox"));
	ChatScrollBox = Cast<UScrollBox>(GetWidgetFromName("ChatScrollBox"));
	ChatInputTextBox = Cast<UEditableTextBox>(GetWidgetFromName("ChatInputTextBox"));
	if (ChatInputTextBox)
	{
		ChatInputTextBox->OnTextChanged.AddDynamic(this, &UChatWidget::ProcessChanged);
		ChatInputTextBox->OnTextCommitted.AddDynamic(this, &UChatWidget::ProcessCommitted);
	}
}

void UChatWidget::UpdatePlayerCount(int32 InPlayerCount)
{
	if (PlayerCountTextBox)
	{
		FString Message = FString::Printf(TEXT("PlayerCount : %d"), InPlayerCount);
		PlayerCountTextBox->SetText(FText::FromString(Message));
	}
}

void UChatWidget::ProcessChanged(const FText& Text)
{

}

void UChatWidget::ProcessCommitted_Implementation(const FText& Text, ETextCommit::Type CommitMethod)
{
	
}

void UChatWidget::AddMessage(const FString& InMessage)
{
	if (ChatScrollBox)
	{
		UTextBlock* NewMessage = NewObject<UTextBlock>(ChatScrollBox);
		if (NewMessage)
		{
			NewMessage->SetText(FText::FromString(InMessage));
			FSlateFontInfo NewFont = NewMessage->GetFont();
			NewFont.Size = 18;
			//NewMessage->SetColorAndOpacity(FSlateColor(FLinearColor(255, 255, 255, 1)));
			NewMessage->SetFont(NewFont);

			ChatScrollBox->AddChild(NewMessage);
			ChatScrollBox->ScrollToEnd();
		}
	}
}
