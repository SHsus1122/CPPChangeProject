// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum EPacketType : unsigned short
{
	RequestLogin = 10,
	ResponseLogin = 20,
	RequestCreateAccount = 30,
	ResponseCreateAccount = 40,
	Max
};

#pragma pack(push, 1)
struct FHeader
{
	unsigned short Size;
	EPacketType Type;
};

struct FRequestLoginData
{
	char Id[20];
	char Password[20];
};

struct FResponseLoginData
{
	bool IsSuccess;
	char Nickname[20];
};
struct FRequestCreateAccountData
{
	char Id[20];
	char Password[20];
	char Nickname[20];
};

struct FResponseCreateAccountData
{
	bool IsSuccess;
};
#pragma pack(pop)
