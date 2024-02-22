// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MessageModal.generated.h"

class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonClickedEvent);

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API UMessageModal : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnCloseButtonClickedEvent OnCloseModalRequest;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UButton> OkWidget;
	
	UPROPERTY(EditInstanceOnly, Category = "Content")
	FText Message;
	
	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void BindButtonClicked();
};
