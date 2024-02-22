// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NicknameInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class TEMPNAMEPROJECT_API UNicknameInterface : public UInterface
{
	GENERATED_BODY()
};

class TEMPNAMEPROJECT_API INicknameInterface
{
	GENERATED_BODY()
public:
	virtual void SetNickname(const FString Nickname) = 0;
	virtual FString GetNickname() = 0;
};