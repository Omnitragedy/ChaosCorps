// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSparksStatics.h"
#include "ChaosCorps.h"
#include <GameSparks/generated/GSRequests.h>
#include "LoginUserWidget.h"

UWorld *UGameSparksStatics::theWorld = nullptr;
bool UGameSparksStatics::initialized = false;

void UGameSparksStatics::InitStatics(UWorld* myWorld) {
	if (!initialized) {
		theWorld = myWorld;
		initialized = true;
	}
}

TArray<FString> UGameSparksStatics::GetOnlinePlayersList() {
	UGameSparksStatics::UpdateNamesOfOnlinePlayers();
	return UGameSparksStatics::playersList;
}

void UGameSparksStatics::LoginRequest_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::AuthenticationResponse &resp) {
	if (initialized) {
		if (!resp.GetHasErrors()) {
			GameSparks::Api::Requests::AccountDetailsRequest accDetailsRequest(gs);

			accDetailsRequest.Send(LoginSuccessDetails_Response);
		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Login failed"));
			}
		}
	}
}

void UGameSparksStatics::LoginSuccessDetails_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::AccountDetailsResponse &resp) {
	if (initialized) {
		if (!resp.GetHasErrors()) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), resp.GetJSONString().c_str());

			
			
			UGameplayStatics::OpenLevel(theWorld, "ThirdPersonExampleMap");
		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Account Details Request Failed"));
			}
		}
	}
}

void UGameSparksStatics::RegistrationRequest_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::RegistrationResponse &resp) {
	if (initialized) {
		if (!resp.GetHasErrors()) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Registration Successful"));
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), resp.GetJSONString().c_str());
		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Registration Failed"));
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), resp.GetJSONString().c_str());
			}
		}
	}
}

void UGameSparksStatics::UpdateNamesOfOnlinePlayers() {
	//get gamesparks instance
	GameSparks::Core::GS& gs = UGameSparksModule::GetModulePtr()->GetGSInstance();
	
	GameSparks::Api::Requests::LogEventRequest request(gs);
	request.SetEventKey("GPL");
	request.Send(GetName_Response);
}

void UGameSparksStatics::GetName_Response(GameSparks::Core::GS& gs, const GameSparks::Api::Responses::LogEventResponse &resp) {
	this->playersList.Empty();
	
	parsePlayersString(resp.GetScriptData().GetValue().GetString("PL").GetValue());	//add the players in the string to array
}

void UGameSparksStatics::parsePlayersString(const std::string& str) {
	
	if (str.length() == 0)
		return;
	

	//by this point, string should be in format: "n1 n2 n3"
	
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(" ", prev);
		if (pos == std::string::npos)
			pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty())
			this->playersList.Push(FString(token.c_str()));
		prev = pos + 1;		//1 = size of delimiter (" ")
	} while (pos < str.length() && prev < str.length());
}
