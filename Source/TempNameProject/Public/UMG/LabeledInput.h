// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LabeledInput.generated.h"

class UEditableTextBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ULabeledInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ULabeledInput(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	FText GetValue() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UTextBlock> LabelWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UEditableTextBox> ValueWidget;

	UPROPERTY(EditInstanceOnly, Category = "Slot")
	float SizeRatioOfLabelToValue;

	UPROPERTY(EditInstanceOnly, Category = "Content")
	FText Label;
	
	UPROPERTY(EditInstanceOnly, Category = "Content")
	FText Hint;

	UPROPERTY(EditInstanceOnly, Category = "Content")
	bool IsPassword;
	
	virtual void NativePreConstruct() override;

private:
	FText Value;
	
	UFUNCTION()
	void BindValueChanged(const FText& Text);
};
