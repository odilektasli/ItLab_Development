// Fill out your copyright notice in the Description page of Project Settings.


#include "SavedGamesHandler.h"
#include "Misc/App.h"

TArray<FString> USavedGamesHandler::GetSavedGamesList()
{
	TArray<FString> Output;
	Output.Empty();
	FString Path;
	
	if (PLATFORM_WINDOWS && !GIsEditor)
	{
		FString AppDataPath = FPlatformProcess::UserSettingsDir();
		FString ProjectName = FApp::GetProjectName();
		FString AppDataProjectPath = AppDataPath + ProjectName;
		Path = AppDataProjectPath + "/Saved/SaveGames/*.sav";

	}
	
	else
	{
		Path = FPaths::ProjectDir() + "Saved/SaveGames/*.sav";

	}
	UE_LOG(LogTemp, Warning, TEXT("Path: %s"), (FPlatformProcess::UserSettingsDir()));
	IFileManager::Get().FindFiles(Output, *Path, true, false);

	return Output;
}
