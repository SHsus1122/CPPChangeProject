// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuthorizationPanel.generated.h"

class UMessageModal;
class UCircularThrobber;
class UButton;
class ULabeledInput;
/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API UAuthorizationPanel : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StartLoading() const;

	UFUNCTION(BlueprintCallable)
	void StopLoading() const;

	UFUNCTION(BlueprintCallable)
	void ShowSuccessMessage() const;

	UFUNCTION(BlueprintCallable)
	void HideSuccessMessage() const;
	
	UFUNCTION(BlueprintCallable)
	void ShowFailMessage() const;

	UFUNCTION(BlueprintCallable)
	void HideFailMessage() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<ULabeledInput> IdWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<ULabeledInput> PasswordWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWIdget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWIdget))
	TObjectPtr<UCircularThrobber> LoadingWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UMessageModal> SuccessMessageWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	TObjectPtr<UMessageModal> FailMessageWidget;
	

	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	virtual void BindConfirmClicked() PURE_VIRTUAL(UAuthorizationPanel::BindConfirmClicked);

	UFUNCTION()
	virtual void BindCloseSuccessMessage() PURE_VIRTUAL(UAuthorizationPanel::BindCloseMessage);
	
	UFUNCTION()
	virtual void BindCloseFailMessage() PURE_VIRTUAL(UAuthorizationPanel::BindCloseMessage);
};
