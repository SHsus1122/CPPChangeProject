// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuthorizationPanel.h"
#include "CreateAccountPanel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreateAccountRequestEvent, const FText&, ID, const FText&,
                                               Password, const FText&, Nickname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenLoginPanelRequestEvent);
/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API UCreateAccountPanel : public UAuthorizationPanel
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnCreateAccountRequestEvent OnCreateAccountRequested;
	
	UPROPERTY(BlueprintAssignable, Category="Button|Event")
	FOnOpenLoginPanelRequestEvent OnOpenLoginPanelRequested;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<ULabeledInput> NicknameWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWIdget))
	TObjectPtr<UButton> BackButton;

	virtual void NativePreConstruct() override;

private:
	virtual void BindConfirmClicked() override;

	virtual void BindCloseSuccessMessage() override;

	virtual void BindCloseFailMessage() override;

	UFUNCTION()
	void BindBackButtonClicked();
};
