// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/NicknameInterface.h"
#include "Interfaces/SocketInterface.h"
#include "TempGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEMPNAMEPROJECT_API UTempGameInstance : public UGameInstance, public ISocketInterface, public INicknameInterface
{
	GENERATED_BODY()

public:
	/**
	 * Server와 연결되어 있는 FSocket을 Instance에 보관합니다.
	 * @param Socket Server와 연결되어 있는 FSocket.
	 */
	virtual void SetSocket(TSharedPtr<FSocket> Socket) override;
	
	/**
	 * Instance가 보관하고 있는 Server와 연결된 FSocket을 반환합니다.
	 * @return Server와 연결되어 있는 FSocket.
	 */
	virtual TSharedPtr<FSocket> GetSocket() override;

	/**
	 * Server에서 가져온 Nickname을 Instance에 저장합니다.
	 * @param InNickname Database에서 가져온 Nickname
	 */
	virtual void SetNickname(const FString InNickname) override;

	/**
	 * Instance에 저장되어 있는 Nickname을 가져옵니다.
	 * @return Instance에 저장되어 있는 Nickname
	 */
	UFUNCTION(BlueprintCallable, Category = "Nickname")
	virtual FString GetNickname() override;

	
protected:
	TSharedPtr<FSocket> ServerSocket;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FString Nickname;
};
