// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SavedGamesHandler.generated.h"

/**
 * 
 */
UCLASS()
class IT_LAB_API USavedGamesHandler : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "SavedGames")
		static TArray<FString> GetSavedGamesList();
	
};
