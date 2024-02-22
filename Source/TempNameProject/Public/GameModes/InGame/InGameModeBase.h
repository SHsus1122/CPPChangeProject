// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API AInGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void RequestLogoutInfo(class AInGamePlayerState* InPlayerState);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ResponseLogoutInfo(class AInGamePlayerState* InPlayerState);

	UFUNCTION(BlueprintCallable)
	AInGamePlayerState* GetLogoutPlayerState(class AInGamePlayerState* InPlayerState);
};
