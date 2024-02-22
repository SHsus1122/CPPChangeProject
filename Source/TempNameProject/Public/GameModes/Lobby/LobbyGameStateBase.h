// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API ALobbyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void IncreasePlayerCount();

	UFUNCTION(BlueprintCallable)
	void DecreasePlayerCount();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerCount, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32 PlayerCount;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	void OnRep_PlayerCount();
};
