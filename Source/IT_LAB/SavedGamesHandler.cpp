// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedGamesHandler.h"

TArray<FString> USavedGamesHandler::GetSavedGamesList()
{
	TArray<FString> Output;
	Output.Empty();
	FString Path = FPaths::ProjectDir() + "Saved/SaveGames/*.sav";
	
	IFileManager::Get().FindFiles(Output, *Path, true, false);

	if (PLATFORM_WINDOWS)
	{

	}
	
	return Output;
}
