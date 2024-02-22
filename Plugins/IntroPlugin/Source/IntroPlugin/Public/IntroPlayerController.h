// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IntroPlayerController.generated.h"

class UUserWidget;
class UInputMappingContext;
class UInputAction;

/**
 *인트로 화면 플레이어 컨트롤러
 */
UCLASS()
class AIntroPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	UUserWidget* IntroWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "[Custom]UIs", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> IntroWidgetClass;

	/**
	*스킵 키 바인딩 함수
	*/
	virtual void SetupInputComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "[Custom]Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IntroIMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "[Custom]Inputs", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SkippingKey;

	/**
	*스킵 발동 함수
	*/
	virtual void IntroSkip();

	UPROPERTY(BlueprintReadOnly, Category = "[Custom]Variables", meta = (AllowPrivateAccess = "true"))
	bool IsIntroSkipped;
};
