// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

class UCreateAccountPanel;
class INicknameInterface;
class ISocketInterface;
class ULoginPanel;
/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	ALoginPlayerController();
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	TSoftObjectPtr<UWorld> NextLevel;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<ULoginPanel> LoginWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UCreateAccountPanel> CreateAccountWidgetClass;
	
	virtual void BeginPlay() override;

	virtual void ConnectServer();

	virtual void InitializeWidgets();

private:
	bool bIsConnected;
	
	TObjectPtr<ULoginPanel> LoginWidget;
	
	TObjectPtr<UCreateAccountPanel> CreateAccountWidget;
	
	TScriptInterface<ISocketInterface> SocketBox;
	
	TScriptInterface<INicknameInterface> NicknameBox;

	UFUNCTION()
	void BindConnectRequest(const FText& ServerIP);

	UFUNCTION()
	void BindLoginRequest(const FText& ID, const FText& Password);
	
	UFUNCTION()
	void BindCreateAccountRequest(const FText& ID, const FText& Password, const FText& Nickname);
	
	UFUNCTION()
	void BindOpenCreateAccountRequest();
	
	UFUNCTION()
	void BindOpenLoginRequest();
	
	UFUNCTION()
	void BindOpenNextLevelRequest();

	UFUNCTION(BlueprintCallable)
	FString GetServerIp(const FText& IP);

	void InitializeSocketBox();

	void InitializeNicknameBox();
	
	bool CustomConnectServer(const FText& ServerIP);

	FString Login(const FText& ID, const FText& Password);

	bool CreateAccount(const FText& ID, const FText& Password, const FText& Nickname);
};
