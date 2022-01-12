// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardDataActor.generated.h"

USTRUCT(BlueprintType)
struct FBoardData {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoardData")
		FVector PointCoordinate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoardData")
		bool IsPointAvailable;

};

USTRUCT()
struct F2DBoardRow {
	GENERATED_BODY()

public:
	TArray<FBoardData> Columns;


	void AddNewColumn()
	{
		FBoardData Dummy;

		Columns.Add(Dummy);
	}

	void Add(FBoardData BoardData) {
		Columns.Add(BoardData);
	}

	FBoardData *operator[] (int32 i) {
		return &Columns[i];
	}

	F2DBoardRow()
	{

	}

};

USTRUCT(BlueprintType)
struct FCoordinateByIndexStruct {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoardData")
		int RowIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoardData")
		int ColumnIndex;
};

UCLASS()
class IT_LAB_API ABoardDataActor : public AActor
{
	GENERATED_BODY()


		public:	
	// Sets default values for this actor's properties
	ABoardDataActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "BoardData")
		int HoleCount;

	UPROPERTY(EditDefaultsOnly, Category = "BoardData")
		TArray<F2DBoardRow> Rows;

	UPROPERTY(BlueprintReadWrite, EditAnywhere = "BoardData")
		FBoardData DummyBoardData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BoardData")
		FVector InitialBoardPointCoordinate;

	UFUNCTION(BlueprintCallable, Category = "BoardData")
		FBoardData FillBoardArray(FVector PointCoordinate, bool IsPointAvailable, int RowIndex, int ColumnIndex);

	UFUNCTION(BlueprintCallable, Category = "BoardData")
		void InitializeArray(int IncomingHoleCount, FVector InComingBoardInitialPoint);

	UFUNCTION(BlueprintCallable, Category = "BoardData")
		FBoardData GetClosestIndex(FVector MouseLocation, int LegCount, bool IsTwoSided, int ReplacementAngle);

	UFUNCTION(BlueprintCallable, Category = "BoardData")
		void ReplaceComponent(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle);

	UFUNCTION(BlueprintCallable, Category = "BoardData")
		FBoardData GetClosestIndexForCableReplacement(FVector WillBeLocatedPoint);

	void ReplaceHorizontally(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex);
	void ReplaceVertically(FVector WillBeLocatedPoint, int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex);
	bool IsHorizontallyAlignable(int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex);
	bool IsVerticallyAlignable(int LegCount, bool IsTwoSided, float ReplacementAngle, FBoardData IncomingBoardData, int RowIndex, int ColumnIndex);
	static void SaveText(FString CoordinatesInString);
};