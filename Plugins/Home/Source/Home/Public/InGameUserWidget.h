// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUserWidget.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class HOME_API UInGameUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UUserWidget* GetInGameChatWidget();

	UUserWidget* GetInGameSoundWidget();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateInGameUserName();

private:
	UFUNCTION(BlueprintCallable)
	bool InGameSoundISVisible();

	UFUNCTION(BlueprintCallable)
	void ToggleVisibleWidget();

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* InGameChatWidget;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* InGameSoundWidget;
};
