// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/LabeledInput.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBoxSlot.h"


ULabeledInput::ULabeledInput(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer), SizeRatioOfLabelToValue(1), IsPassword(false)
{
}

FText ULabeledInput::GetValue() const
{
	return Value;
}

void ULabeledInput::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (IsValid(LabelWidget))
	{
		LabelWidget->SetText(Label);
	}

	if (IsValid(ValueWidget))
	{
		FSlateChildSize SlateChildSize;
		SlateChildSize.SizeRule = ESlateSizeRule::Fill;
		SlateChildSize.Value = SizeRatioOfLabelToValue;
		Cast<UHorizontalBoxSlot>(ValueWidget->Slot)->SetSize(SlateChildSize);
		ValueWidget->SetHintText(Hint);
		ValueWidget->SetText(Value);
		ValueWidget->SetIsPassword(IsPassword);
		ValueWidget->OnTextChanged.AddDynamic(this, &ULabeledInput::BindValueChanged);
	}
}

void ULabeledInput::BindValueChanged(const FText& Text)
{
	Value = Text;
}
