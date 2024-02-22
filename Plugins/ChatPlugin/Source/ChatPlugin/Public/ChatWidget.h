// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

class UTextBlock;
class UScrollBox;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class CHATPLUGIN_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void UpdatePlayerCount(int32 InPlayerCount);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UTextBlock> PlayerCountTextBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UScrollBox> ChatScrollBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "UI")
	TObjectPtr<UEditableTextBox> ChatInputTextBox;

	UFUNCTION()
	void ProcessChanged(const FText& Text);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ProcessCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	void ProcessCommitted_Implementation(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void AddMessage(const FString& InMessage);
};
