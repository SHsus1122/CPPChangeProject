// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MessageModal.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UMessageModal::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	
	if (IsValid(MessageWidget))
	{
		MessageWidget->SetText(Message);
	}

	if (IsValid(OkWidget))
	{
		OkWidget->OnClicked.AddDynamic(this, &UMessageModal::BindButtonClicked);
	}
}

void UMessageModal::BindButtonClicked()
{
	OnCloseModalRequest.Broadcast();
}
