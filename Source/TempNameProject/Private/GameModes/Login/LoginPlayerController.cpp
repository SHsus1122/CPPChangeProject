// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/Login/LoginPlayerController.h"
#include "UMG/LoginPanel.h"
#include "UMG/CreateAccountPanel.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/NicknameInterface.h"
#include "Interfaces/SocketInterface.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Kismet/GameplayStatics.h"
#include "Network/Packet.h"


ALoginPlayerController::ALoginPlayerController()
{
	SetShowMouseCursor(true);
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();
	InitializeSocketBox();
	InitializeNicknameBox();
	//ConnectServer();
	//InitializeWidgets();

	if (IsValid(LoginWidgetClass))
	{
		LoginWidget = TObjectPtr<ULoginPanel>(CreateWidget<ULoginPanel>(this, LoginWidgetClass, FName("LoginWidget")));
		if (IsValid(LoginWidget)) {
			LoginWidget->OnConnectRequested.AddDynamic(this, &ALoginPlayerController::BindConnectRequest);
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(LoginWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputMode);
			LoginWidget->AddToViewport();
		}
	}
	if (IsValid(CreateAccountWidgetClass))
	{
		CreateAccountWidget = TObjectPtr<UCreateAccountPanel>(CreateWidget<UCreateAccountPanel>(this, CreateAccountWidgetClass, FName("CreateWidget")));
	}
}

void ALoginPlayerController::ConnectServer()
{
	const TSharedPtr<FSocket> Socket = MakeShareable(
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket")));
	const FString AddressString = TEXT("127.0.0.1");
	FIPv4Address IP;
	FIPv4Address::Parse(AddressString, IP);
	constexpr int32 Port = 12345;
	const TSharedRef<FInternetAddr> Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Address->SetIp(IP.Value);
	Address->SetPort(Port);
	bIsConnected = Socket->Connect(*Address);
	if (bIsConnected)
	{
		SocketBox->SetSocket(Socket);
	}
}

void ALoginPlayerController::InitializeWidgets()
{
	if (IsValid(LoginWidgetClass))
	{
		if (IsValid(LoginWidget))
		{
			LoginWidget->OnLoginRequested.AddDynamic(this, &ALoginPlayerController::BindLoginRequest);
			LoginWidget->OnOpenCreateAccountPanelRequested.AddDynamic(this, &ALoginPlayerController::BindOpenCreateAccountRequest);
			LoginWidget->OnOpenNextLevelRequested.AddDynamic(this, &ALoginPlayerController::BindOpenNextLevelRequest);
		}
	}
	if (IsValid(CreateAccountWidgetClass))
	{
		if (IsValid(CreateAccountWidget))
		{
			CreateAccountWidget->OnCreateAccountRequested.AddDynamic(this, &ALoginPlayerController::BindCreateAccountRequest);
			CreateAccountWidget->OnOpenLoginPanelRequested.AddDynamic(this, &ALoginPlayerController::BindOpenLoginRequest);
		}
	}
}

void ALoginPlayerController::BindConnectRequest(const FText& ServerIP)
{
	const bool bIsSuccess = CustomConnectServer(ServerIP);
	if (!bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is disconnected."))
		return;
	}	
	LoginWidget->StartLoading();
	LoginWidget->StopLoading();
	if (!bIsSuccess)
	{
		CreateAccountWidget->ShowFailMessage();
	}
	else
	{
		CreateAccountWidget->ShowSuccessMessage();
		InitializeWidgets();
	}
}

void ALoginPlayerController::BindLoginRequest(const FText& ID, const FText& Password)
{
	if(!bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is disconnected."))
		return;
	}
	LoginWidget->StartLoading();
	const FString Nickname = Login(ID, Password);
	LoginWidget->StopLoading();

	if (Nickname.IsEmpty())
	{
		LoginWidget->ShowFailMessage();
	}
	else
	{
		NicknameBox->SetNickname(Nickname);
		LoginWidget->ShowSuccessMessage();
	}
}

void ALoginPlayerController::BindCreateAccountRequest(const FText& ID, const FText& Password, const FText& Nickname)
{
	if(!bIsConnected)
	{
		UE_LOG(LogTemp, Warning, TEXT("Server is disconnected."))
		return;
	}
	CreateAccountWidget->StartLoading();
	const bool bIsSuccess = CreateAccount(ID, Password, Nickname);
	CreateAccountWidget->StopLoading();
	if (!bIsSuccess)
	{
		CreateAccountWidget->ShowFailMessage();
	}
	else
	{
		CreateAccountWidget->ShowSuccessMessage();
	}
}

void ALoginPlayerController::BindOpenCreateAccountRequest()
{
	LoginWidget->RemoveFromParent();
	CreateAccountWidget->AddToViewport();
}

void ALoginPlayerController::BindOpenLoginRequest()
{
	CreateAccountWidget->RemoveFromParent();
	LoginWidget->AddToViewport();
}

void ALoginPlayerController::BindOpenNextLevelRequest()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), NextLevel);
}

FString ALoginPlayerController::GetServerIp(const FText& IP)
{
	return FString();
}

void ALoginPlayerController::InitializeSocketBox()
{
	SocketBox.SetInterface(Cast<ISocketInterface>(GetGameInstance()));
	SocketBox.SetObject(GetGameInstance());
}

void ALoginPlayerController::InitializeNicknameBox()
{
	NicknameBox.SetInterface(Cast<INicknameInterface>(GetGameInstance()));
	NicknameBox.SetObject(GetGameInstance());
}

bool ALoginPlayerController::CustomConnectServer(const FText& ServerIP)
{
	const TSharedPtr<FSocket> Socket = MakeShareable(
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket")));
	const FString AddressString = ServerIP.ToString();
	FIPv4Address IP;
	FIPv4Address::Parse(AddressString, IP);
	constexpr int32 Port = 12345;
	const TSharedRef<FInternetAddr> Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Address->SetIp(IP.Value);
	Address->SetPort(Port);
	bIsConnected = Socket->Connect(*Address);
	if (bIsConnected)
	{
		SocketBox->SetSocket(Socket);
		return true;
	}
	return false;
}

FString ALoginPlayerController::Login(const FText& ID, const FText& Password)
{
	int32 Sent = 0;
	
	FHeader SendHeader;
	SendHeader.Size = sizeof(FRequestLoginData);
	SendHeader.Type = RequestLogin;
	SocketBox->GetSocket()->Send((uint8*)&SendHeader, sizeof(SendHeader), Sent);
	
	FRequestLoginData RequestData = {};
	StringToBytes(ID.ToString(), (uint8*)&RequestData.Id, sizeof(RequestData.Id));
	StringToBytes(Password.ToString(), (uint8*)&RequestData.Password, sizeof(RequestData.Password));
	SocketBox->GetSocket()->Send((uint8*)&RequestData, sizeof(RequestData), Sent);

	
	FHeader ReceiveHeader = {};
	int32 Read = 0;
	SocketBox->GetSocket()->Recv((uint8*)&ReceiveHeader, sizeof(ReceiveHeader), Read, ESocketReceiveFlags::WaitAll);

	if(ReceiveHeader.Type != ResponseLogin)
	{
		return FString();
	}
	
	FResponseLoginData ResponseData = {};
	SocketBox->GetSocket()->Recv((uint8*)&ResponseData, sizeof(ResponseData), Read, ESocketReceiveFlags::WaitAll);
	
	if (!ResponseData.IsSuccess)
	{
		return FString();
	}
	return FString(ResponseData.Nickname);
}

bool ALoginPlayerController::CreateAccount(const FText& ID, const FText& Password, const FText& Nickname)
{
	int32 Sent = 0;
	
	FHeader SendHeader;
	SendHeader.Size = sizeof(FRequestCreateAccountData);
	SendHeader.Type = RequestCreateAccount;
	SocketBox->GetSocket()->Send((uint8*)&SendHeader, sizeof(SendHeader), Sent);
	
	FRequestCreateAccountData RequestData = {};
	StringToBytes(ID.ToString(), (uint8*)&RequestData.Id, sizeof(RequestData.Id));
	StringToBytes(Password.ToString(), (uint8*)&RequestData.Password, sizeof(RequestData.Password));
	StringToBytes(Nickname.ToString(), (uint8*)&RequestData.Nickname, sizeof(RequestData.Nickname));
	SocketBox->GetSocket()->Send((uint8*)&RequestData, sizeof(RequestData), Sent);

	
	FHeader ReceiveHeader = {};
	int32 Read = 0;
	SocketBox->GetSocket()->Recv((uint8*)&ReceiveHeader, sizeof(ReceiveHeader), Read, ESocketReceiveFlags::WaitAll);

	if(ReceiveHeader.Type != ResponseCreateAccount)
	{
		return false;
	}
	
	FResponseCreateAccountData ResponseData = {};
	SocketBox->GetSocket()->Recv((uint8*)&ResponseData, sizeof(ResponseData), Read, ESocketReceiveFlags::WaitAll);
	return ResponseData.IsSuccess;
}
