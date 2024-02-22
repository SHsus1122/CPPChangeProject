// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyRoomUserWidget.h"

void ULobbyRoomUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

UUserWidget* ULobbyRoomUserWidget::GetLobbyChatWidget()
{
	return LobbyChatWidget;
}

UUserWidget* ULobbyRoomUserWidget::GetLobbySoundWidget()
{
	return LobbySoundWidget;
}

bool ULobbyRoomUserWidget::LobbySoundISVisible()
{
	return LobbySoundWidget->IsVisible();
}

void ULobbyRoomUserWidget::ToggleVisibleWidget()
{
	if (LobbySoundISVisible())
	{
		LobbySoundWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		LobbySoundWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
