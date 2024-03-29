// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPETUT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
	
	UPROPERTY(EditAnywhere) float Reach = 250.0f;
	
	void Grab();
	void Release();
	void SetupInputComponent();
	void SetupPhysicsHandle();
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetRayTraceEnd() const;
	FVector GetPlayerViewPointLocation() const;
	FRotator GetPlayerViewPointRotation() const;
};
