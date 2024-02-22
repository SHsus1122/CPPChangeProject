// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EntryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class HOME_API UEntryUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UUserWidget* GetEntrySoundWidget();

private:
	UFUNCTION()
	bool EntrySoundISVisible();

	UFUNCTION(BlueprintCallable)
	void ToggleVisibleWidget();

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	UUserWidget* EntrySoundWidget;
};
