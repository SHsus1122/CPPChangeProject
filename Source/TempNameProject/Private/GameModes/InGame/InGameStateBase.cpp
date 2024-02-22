// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/InGame/InGameStateBase.h"
#include "GameModes/InGame/InGamePlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void AInGameStateBase::IncreasePlayerCount()
{
	PlayerCount++;
}

void AInGameStateBase::DecreasePlayerCount()
{
	PlayerCount--;
}

void AInGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGameStateBase, PlayerCount);
}

void AInGameStateBase::OnRep_PlayerCount()
{
	AInGamePlayerController* IPC = Cast<AInGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IPC && IPC->ChatWidget)
	{
		IPC->ChatWidget->UpdatePlayerCount(PlayerCount);
	}
}