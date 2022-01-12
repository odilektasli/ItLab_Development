// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CableBaseActor.generated.h"

UCLASS()
class IT_LAB_API ACableBaseActor : public AActor
{
	GENERATED_BODY()

		ACableBaseActor();
	
public:	
	// Sets default values for this actor's properties
	float* CableVoltageValuePointer;
	
	UFUNCTION(BlueprintCallable, Category = "CableActor")
		void AssignPointer(ACableBaseActor *CableBaseActor);

	UFUNCTION(BlueprintCallable, Category = "CableActor")
		float GetVoltageValue();

	UFUNCTION(BlueprintCallable, Category = "CableActor")
		void AssignVoltageValue(float IncomingVoltageValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
