// Fill out your copyright notice in the Description page of Project Settings.


#include "CableBaseActor.h"

// Sets default values
ACableBaseActor::ACableBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	float dummyfloat = 0.0f;
	CableVoltageValuePointer = &dummyfloat;


}

void ACableBaseActor::AssignPointer(ACableBaseActor* CableBaseActor)
{
	CableVoltageValuePointer = CableBaseActor->CableVoltageValuePointer;
}

float ACableBaseActor::GetVoltageValue()
{
	return *CableVoltageValuePointer;
}

void ACableBaseActor::AssignVoltageValue(float IncomingVoltageValue)
{
	*CableVoltageValuePointer = 30.0f;
}


// Called when the game starts or when spawned
void ACableBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACableBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

