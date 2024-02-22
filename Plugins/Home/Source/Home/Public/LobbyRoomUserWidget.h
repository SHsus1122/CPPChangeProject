// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyRoomUserWidget.generated.h"

class UUserWidget;

/**
 *
 */
UCLASS()
class HOME_API ULobbyRoomUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UUserWidget* GetLobbyChatWidget();

	UUserWidget* GetLobbySoundWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateLobbyUserName();

private:
	UFUNCTION()
	bool LobbySoundISVisible();

	UFUNCTION(BlueprintCallable)
	void ToggleVisibleWidget();

protected:
	// EditDefaultsOnly : 본인만 수정 가능
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* LobbyChatWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* LobbySoundWidget;
};
