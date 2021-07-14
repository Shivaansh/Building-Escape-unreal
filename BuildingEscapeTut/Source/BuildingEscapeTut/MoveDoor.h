// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Containers/Array.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h" //needed for GetObject() method
#include "GameFramework/PlayerController.h"
#include "Math/Rotator.h"
#include "Math/UnrealMathUtility.h" 	
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
	void CloseDoor(float DeltaTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float TotalMass() const;

private:
	
	float doorRotation = 90.0f;
	float doorLastOpened;
	float currentRotation;
	float initialRotation;

	UPROPERTY(EditAnywhere)	int doorSpeed = 75;
	UPROPERTY(EditAnywhere)	float doorCloseDelay = 0.8f;
	UPROPERTY(EditAnywhere)	float targetRotation;
	UPROPERTY(EditAnywhere)	float plateMass = 15.0f;
	UPROPERTY(EditAnywhere) ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere) AActor* DoorOpener = nullptr;
	UPROPERTY(EditAnywhere) UAudioComponent* AudioPlayer = nullptr;
		
};
