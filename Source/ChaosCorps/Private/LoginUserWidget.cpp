// Fill out your copyright notice in the Description page of Project Settings.

#include "LoginUserWidget.h"
#include "CCStateManager.h"

void ULoginUserWidget::OnLoginClicked()
{
	if (GetWorld()->GetGameInstance()) {
		UCCStateManager *manager = Cast<UCCStateManager>(GetWorld()->GetGameInstance());
		manager->Login(username, password);
	}
}

void ULoginUserWidget::OnRegisterClicked()
{
	if (username.Contains(" ")) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::MakeRandomColor(), TEXT("Cannot have space in Username"));
		}
	} else if (GetWorld()->GetGameInstance()) {
		UCCStateManager *manager = Cast<UCCStateManager>(GetWorld()->GetGameInstance());
		manager->Register(username, password);
	}
}

void ULoginUserWidget::OnQuitClicked()
{
	#if WITH_EDITOR
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	#endif
	#if !WITH_EDITOR
		FGenericPlatformMisc::RequestExit(false);
	#endif
}
