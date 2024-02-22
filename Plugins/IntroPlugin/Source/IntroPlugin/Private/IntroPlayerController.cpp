// Fill out your copyright notice in the Description page of Project Settings.


#include "IntroPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "IntroUserWidget.h"



void AIntroPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IntroIMC, 0);
	}

	bShowMouseCursor = false;

	IntroWidget = CreateWidget<UUserWidget>(GetWorld(), IntroWidgetClass);
	IntroWidget->AddToViewport();
}

void AIntroPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* UEIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		UEIC->BindAction(SkippingKey, ETriggerEvent::Started, this, &AIntroPlayerController::IntroSkip);
	}
}

void AIntroPlayerController::IntroSkip()
{
	IsIntroSkipped = true;
	if (IsIntroSkipped)
	{
		UIntroUserWidget* UIUW = Cast<UIntroUserWidget>(IntroWidget);
		UIUW->OnVideoEnd();
	}
}