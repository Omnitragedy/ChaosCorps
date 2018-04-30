// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSCORPS_API ULoginUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Login Screen")
		FString username;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Login Screen")
		FString password;
	

	UFUNCTION(BlueprintCallable, Category = "Login Screen")
		void OnLoginClicked();

	UFUNCTION(BlueprintCallable, Category = "Login Screen")
		void OnRegisterClicked();

	UFUNCTION(BlueprintCallable, Category = "Login Screen")
		void OnQuitClicked();
	
	
};
