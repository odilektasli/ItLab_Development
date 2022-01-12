// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardDataActor.h"

// Sets default values
ABoardDataActor::ABoardDataActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoardDataActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoardDataActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FBoardData ABoardDataActor::FillBoardArray(FVector PointCoordinate, bool IsPointAvailable, int RowIndex, int ColumnIndex)
{
	FBoardData BoardData;
	BoardData.PointCoordinate = PointCoordinate;
	BoardData.IsPointAvailable = IsPointAvailable;
	Rows[RowIndex].Columns.Add(BoardData);
	
	
	return BoardData;
	

	
	
	
}

void ABoardDataActor::InitializeArray(int IncomingHoleCount, FVector InComingBoardInitialPoint)
{

	InitialBoardPointCoordinate = InComingBoardInitialPoint;

	HoleCount = IncomingHoleCount;

	for (int32 Index = 0; Index < HoleCount; Index++)
	{
		Rows.Add(F2DBoardRow());
	}

	for (int32 Index = 0; Index < HoleCount; Index++)
	{
		for (int32 InnerIndex = 0; Index < HoleCount; Index++)
		{
			Rows[Index].AddNewColumn();
		}
	}

}

FBoardData ABoardDataActor::GetClosestIndex(FVector MouseLocation, int LegCount, bool IsTwoSided, int ReplacementAngle)
{
	bool HorizontallyAlignability = false, VerticallyAlignability = false;
	FVector IndexCalculatorVector = MouseLocation - InitialBoardPointCoordinate;

	int32 RowIndex = (int32)roundf(IndexCalculatorVector.Y / 200.0f);
	int32 ColumnIndex = (int32)roundf(IndexCalculatorVector.X / 200.0f) + 1; // The location is on negative side

	FBoardData ReturnedBoardData;
	ReturnedBoardData.IsPointAvailable = false;
	ReturnedBoardData.PointCoordinate = Rows[FMath::Clamp(RowIndex, 0, Rows.Num() - 1)][FMath::Clamp(ColumnIndex , 0, Rows[0].Columns.Num() - 1)]->PointCoordinate;

	if (ReplacementAngle == 0 || ReplacementAngle == -180)
	{
		IsHorizontallyAlignable(LegCount, IsTwoSided, ReplacementAngle, DummyBoardData, RowIndex, ColumnIndex) ? HorizontallyAlignability = true : HorizontallyAlignability = false;
	}
	else if (ReplacementAngle == 90 || ReplacementAngle == -90)
	{
		IsVerticallyAlignable(LegCount, IsTwoSided, ReplacementAngle, DummyBoardData, RowIndex, ColumnIndex) ? VerticallyAlignability = true : VerticallyAlignability = false;
	}

	if (VerticallyAlignability || HorizontallyAlignability)
	{
		ReturnedBoardData.IsPointAvailable = true;

	}

	UE_LOG(LogTemp, Error, TEXT("RowIndex %d: ColumnIndex: %d Availability: %d"), FMath::Clamp(RowIndex, 0, Rows.Num() - 1), FMath::Clamp(ColumnIndex, 0, Rows[0].Columns.Num() - 1), Rows[FMath::Clamp(RowIndex, 0, Rows.Num() - 1)][FMath::Clamp(ColumnIndex, 0, Rows[0].Columns.Num() - 1)]->IsPointAvailable);
	return ReturnedBoardData;

	return *Rows[FMath::Clamp(RowIndex, 0, Rows.Num() - 1)][FMath::Clamp(ColumnIndex, 0, Rows[0].Columns.Num() - 1)];
}


void ABoardDataActor::ReplaceComponent(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle)
{
	FVector IndexCalculatorVector = WillBeLocatedPoint - InitialBoardPointCoordinate;

	int32 RowIndex = (int32)roundf(IndexCalculatorVector.Y / 200.0f);
	int32 ColumnIndex = (int32)roundf(IndexCalculatorVector.X / 200.0f) + 1;
	DummyBoardData.IsPointAvailable = false;


	if (ReplacementAngle == 0 || ReplacementAngle == -180)
	{
		ReplaceHorizontally(WillBeLocatedPoint, LegCount, IsTwoSided, ReplacementAngle, DummyBoardData, RowIndex, ColumnIndex);
	}
	else if (ReplacementAngle == 90 || ReplacementAngle == -90)
	{
		ReplaceVertically(WillBeLocatedPoint, LegCount, IsTwoSided, ReplacementAngle, DummyBoardData, RowIndex, ColumnIndex);
	}

}

FBoardData ABoardDataActor::GetClosestIndexForCableReplacement(FVector WillBeLocatedPoint)
{
	FVector IndexCalculatorVector = WillBeLocatedPoint - InitialBoardPointCoordinate;

	int32 RowIndex = (int32)roundf(IndexCalculatorVector.Y / 200.0f);
	int32 ColumnIndex = (int32)roundf(IndexCalculatorVector.X / 200.0f) + 1;

	return *Rows[FMath::Clamp(RowIndex, 0, Rows.Num() - 1)][FMath::Clamp(ColumnIndex, 0, Rows[0].Columns.Num() - 1)];
}

void ABoardDataActor::ReplaceHorizontally(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData,int RowIndex, int ColumnIndex)
{
	int Direction = 1;

	if (ReplacementAngle == 0)
	{
		Direction = 1;
	}

	if (ReplacementAngle == -180)
	{
		Direction = -1;
	}
	
	for (int Index = 0; Index < LegCount; Index++)
	{
		DummyBoardData.PointCoordinate = Rows[RowIndex][ColumnIndex - Index * Direction]->PointCoordinate;
		*Rows[RowIndex][ColumnIndex - Index * Direction] = DummyBoardData;
	}

	if (IsTwoSided)
	{
		for (int Index = 0; Index < LegCount; Index++)
		{
			DummyBoardData.PointCoordinate = Rows[RowIndex - 1][ColumnIndex - Index * Direction]->PointCoordinate;
			*Rows[RowIndex - 1][ColumnIndex - Index * Direction] = DummyBoardData;
			UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d"), RowIndex - 1, ColumnIndex - Index);
		}
	}
	
}

void ABoardDataActor::ReplaceVertically(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex)
{
	int Direction = 1;

	if (ReplacementAngle == 90)
	{
		Direction = 1;
	}

	if (ReplacementAngle == -90)
	{
		Direction = -1;
	}

	for (int Index = 0; Index < LegCount; Index++)
	{
		DummyBoardData.PointCoordinate = Rows[RowIndex - Index * Direction ][ColumnIndex ]->PointCoordinate;
		*Rows[RowIndex - Index * Direction][ColumnIndex] = DummyBoardData;
	}

	if (IsTwoSided)
	{
		for (int Index = 0; Index < LegCount; Index++)
		{
			DummyBoardData.PointCoordinate = Rows[RowIndex - Index * Direction][ColumnIndex + 1]->PointCoordinate;
			*Rows[RowIndex - Index * Direction][ColumnIndex + 1] = DummyBoardData;
			UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d"), RowIndex - 1, ColumnIndex - Index);
		}
	}
}

bool ABoardDataActor::IsHorizontallyAlignable(int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex)
{
	int Direction = 1;

	if (ReplacementAngle == 0)
	{
		Direction = 1;
	}

	if (ReplacementAngle == -180)
	{
		Direction = -1;
	}

	for (int Index = 0; Index < LegCount; Index++)
	{
		if (!Rows[RowIndex][ColumnIndex - (Index * Direction)]->IsPointAvailable)
		{

			return false;
			UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d Availability: %d"), RowIndex, ColumnIndex - Index, Rows[RowIndex][ColumnIndex - Index]->IsPointAvailable);
			/*return ReturnedBoardData;*/
		}
	}

	if (IsTwoSided)
	{
		for (int Index = 0; Index < LegCount; Index++)
		{
			if (!Rows[RowIndex - 1][ColumnIndex - (Index * Direction)]->IsPointAvailable)
			{
				return false;
				UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d Availability: %d"), RowIndex - 1, ColumnIndex - Index, Rows[RowIndex][ColumnIndex - Index]->IsPointAvailable);
				/*return ReturnedBoardData;*/
			}
		}
	}

	return true;
}

bool ABoardDataActor::IsVerticallyAlignable(int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex)
{
	int Direction = 1;

	if (ReplacementAngle == 90)
	{
		Direction = 1;
	}

	if (ReplacementAngle == -90)
	{
		Direction = -1;
	}

	for (int Index = 0; Index < LegCount; Index++)
	{
		if (!Rows[RowIndex - (Index * Direction)][ColumnIndex]->IsPointAvailable)
		{

			return false;
			UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d Availability: %d"), RowIndex, ColumnIndex - Index, Rows[RowIndex][ColumnIndex - Index]->IsPointAvailable);
			/*return ReturnedBoardData;*/
		}
	}

	if (IsTwoSided)
	{
		for (int Index = 0; Index < LegCount; Index++)
		{
			if (!Rows[RowIndex - (Index * Direction)][ColumnIndex + 1]->IsPointAvailable)
			{
				return false;
				UE_LOG(LogTemp, Warning, TEXT("RowIndex %d: ColumnIndex: %d Availability: %d"), RowIndex - 1, ColumnIndex - Index, Rows[RowIndex][ColumnIndex - Index]->IsPointAvailable);
				/*return ReturnedBoardData;*/
			}
		}
	}

	return true;
}

void ABoardDataActor::SaveText(FString CoordinatesInString)
{
	FFileHelper::SaveStringToFile(CoordinatesInString, *(FPaths::GameSourceDir() + TEXT("Coordinates.txt")));
}



