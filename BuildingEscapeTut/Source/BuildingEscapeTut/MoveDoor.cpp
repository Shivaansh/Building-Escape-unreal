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
	AudioPlayer = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioPlayer){
		UE_LOG(LogTemp, Error, TEXT("NO AUDIO COMPONENT FOUND!"));
	}else{
		UE_LOG(LogTemp, Error, TEXT("AUDIO COMPONENT FOUND: %s"), *(AudioPlayer->GetName()));
	}
}


// Called every frame
void UMoveDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(!DoorOpener){
		UE_LOG(LogTemp, Error, TEXT("NO DoorOpener assigned!"));
		return;
	}
	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("NO PressurePlate assigned!"));
		return;
	}
	float MassOfObjects = TotalMass();
	if(PressurePlate){
		if(MassOfObjects > plateMass){
			OpenDoor(DeltaTime);
			// doorLastOpened = GetWorld()->GetTimeSeconds();	
		}else{
			CloseDoor(DeltaTime);
		}
	}
}

void UMoveDoor::OpenDoor(float DeltaTime){
	currentRotation = FMath::FInterpTo(currentRotation, targetRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenOutwardsRotation = FRotator();
	OpenOutwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenOutwardsRotation);
	if(AudioPlayer){
		UE_LOG(LogTemp, Warning, TEXT("PLAYING AUDIO"));
		AudioPlayer->Play();
	}
	
}

void UMoveDoor::CloseDoor(float DeltaTime){
	currentRotation = FMath::FInterpTo(currentRotation, initialRotation, DeltaTime, DeltaTime*doorSpeed);
	FRotator OpenInwardsRotation = FRotator();
	OpenInwardsRotation.Yaw = currentRotation;
	GetOwner()->SetActorRotation(OpenInwardsRotation);
	if(AudioPlayer){
		UE_LOG(LogTemp, Warning, TEXT("PLAYING AUDIO"));
		AudioPlayer->Play();
	}
}

float UMoveDoor::TotalMass() const{
	
	OUT float mass = 0.0f;
	
	TArray<AActor*> OverlappingObjects;
	PressurePlate->GetOverlappingActors(OverlappingObjects);
	if(!PressurePlate){
		UE_LOG(LogTemp, Error, TEXT("NO PressurePlate assigned!"));
		return 0.0f;
	}
	for(AActor* Actor : OverlappingObjects){
		mass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Mass is %f"), mass);
	return mass;

}