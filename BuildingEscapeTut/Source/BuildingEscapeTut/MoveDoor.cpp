// Fill out your copyright notice in the Description page of Project Settings.
#include "MoveDoor.h"

#define OUT

// Sets default values for this component's properties
UMoveDoor::UMoveDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveDoor::BeginPlay()
{
	Super::BeginPlay();

	currentRotation = GetOwner()->GetActorRotation().Yaw;
	initialRotation = currentRotation;
	targetRotation = initialRotation + doorRotation;
	UE_LOG(LogTemp, Warning, TEXT("Object yaw transform before rotating is %f"), (GetOwner()->GetActorRotation()).Yaw);
	DoorOpener = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	float MassOfObjects = TotalMass();
	if(PressurePlate){
		if(MassOfObjects > plateMass){
			OpenDoor(DeltaTime);
			// doorLastOpened = GetWorld()->GetTimeSeconds();	
		}else{
			CloseDoor(DeltaTime);
		}
		
	}
	if(!DoorOpener){
		UE_LOG(LogTemp, Error, TEXT("NO DoorOpener assigned!"));
	}
	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("NO PressurePlate assigned!"));
	}
}

void UMoveDoor::OpenDoor(float DeltaTime){
	currentRotation = FMath::FInterpTo(currentRotation, targetRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenOutwardsRotation = FRotator();
	OpenOutwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenOutwardsRotation);
}

void UMoveDoor::CloseDoor(float DeltaTime){
	currentRotation = FMath::FInterpTo(currentRotation, initialRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenInwardsRotation = FRotator();
	OpenInwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenInwardsRotation);
}

float UMoveDoor::TotalMass() const{
	
	OUT float mass = 0.0f;
	
	TArray<AActor*> OverlappingObjects;
	PressurePlate->GetOverlappingActors(OverlappingObjects);

	for(AActor* Actor : OverlappingObjects){
		mass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Mass is %f"), mass);
	return mass;

}