// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SocketInterface.generated.h"

/**
 * 
 */
UINTERFACE()
class TEMPNAMEPROJECT_API USocketInterface : public UInterface 
{
    GENERATED_BODY()
};

class TEMPNAMEPROJECT_API ISocketInterface
{
	GENERATED_BODY()
public:
	virtual void SetSocket(TSharedPtr<FSocket> Socket) = 0;
	virtual TSharedPtr<FSocket> GetSocket() = 0;
};