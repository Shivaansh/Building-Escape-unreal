// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h" //needed for GetObject() method
#include "CoreMinimal.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h" 	
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MoveDoor.generated.h"


// Add members, member variables and functions here


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPETUT_API UMoveDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveDoor();
	void OpenDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float doorOpenRotation = 90.0f;
	float currentRotation;
	float initialRotation;
	UPROPERTY(EditAnywhere)	float targetRotation;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere) AActor* DoorOpener;
	

		
};
