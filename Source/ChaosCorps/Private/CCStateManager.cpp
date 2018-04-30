// Fill out your copyright notice in the Description page of Project Settings.

#include "CCStateManager.h"
#include "ChaosCorps.h"
#include "GameSparksStatics.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

void UCCStateManager::Init()
{
	Super::Init();

	currentState = EGameState::ENone;
	currentWidget = nullptr;
}

void UCCStateManager::ChangeState(EGameState newState)
{
	//ifthe desired stae is not the current state
	if (newState != currentState) {
		LeaveState(currentState);
		EnterState(newState);
	}
}

EGameState UCCStateManager::GetGameState()
{
	return currentState;
}

void UCCStateManager::Login(FString username, FString password) {
	if (username.IsEmpty() || password.IsEmpty()) {
		return;
	}
	
	//get gamesparks instance
	GameSparks::Core::GS& gs = UGameSparksModule::GetModulePtr()->GetGSInstance();
	
	//begin login request
	GameSparks::Api::Requests::AuthenticationRequest req(gs);
	
	//set user and password
	req.SetUserName(std::string(TCHAR_TO_UTF8(*username)));
	req.SetPassword(std::string(TCHAR_TO_UTF8(*password)));
	
	//send request
	req.Send(UGameSparksStatics::LoginRequest_Response);
}

void UCCStateManager::Register(FString username, FString password)
{
	if (username.IsEmpty() || password.IsEmpty()) {
		return;
	}

	//get gamesparks instance
	GameSparks::Core::GS& gs = UGameSparksModule::GetModulePtr()->GetGSInstance();

	//begin reg. request
	GameSparks::Api::Requests::RegistrationRequest req(gs);

	//set usr, pass, disp
	req.SetUserName(std::string(TCHAR_TO_UTF8(*username)));
	req.SetPassword(std::string(TCHAR_TO_UTF8(*password)));
	req.SetDisplayName(std::string(TCHAR_TO_UTF8(*username)));

	//send request
	req.Send(UGameSparksStatics::RegistrationRequest_Response);
}

void UCCStateManager::EnterState(EGameState newState)
{
	//set new state
	currentState = newState;

	switch (currentState) {
		case EGameState::EStartup: {
			break;
		}
		case EGameState::ELoginScreen: {
			currentWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), cLoginMenu);
			currentWidget->AddToViewport();

			FInputModeUIOnly mode;
			GetWorld()->GetFirstPlayerController()->SetInputMode(mode);
			GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
			break;
		}
		case EGameState::ENone: {
			break;
		}
	}
}

void UCCStateManager::LeaveState(EGameState oldState)
{
	switch (currentState) {
		case EGameState::EStartup: {
			break;
		}
		case EGameState::ELoginScreen: {
			break;
		}
		case EGameState::ENone: {
			break;
		}
	}
	
	EnterState(EGameState::ENone);

}
