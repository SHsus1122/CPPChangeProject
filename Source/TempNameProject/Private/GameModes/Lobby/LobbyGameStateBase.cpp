// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Lobby/LobbyGameStateBase.h"
#include "GameModes/Lobby/LobbyPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

void ALobbyGameStateBase::IncreasePlayerCount()
{
	PlayerCount++;
}

void ALobbyGameStateBase::DecreasePlayerCount()
{
	PlayerCount--;
}

void ALobbyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGameStateBase, PlayerCount);
}

void ALobbyGameStateBase::OnRep_PlayerCount()
{
	ALobbyPlayerController* LPC = Cast<ALobbyPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (LPC && LPC->ChatWidget)
	{
		LPC->ChatWidget->UpdatePlayerCount(PlayerCount);
	}
}
