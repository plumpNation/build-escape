#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#include "GrabberComponent.h"

#define OUT

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("I am a grabber"));
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector outLocation;
	FRotator outRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT outLocation, OUT outRotation);

	FVector lineTraceEnd = outLocation + FVector(0.f, 0.f, 100.f); // 1 meter up

	DrawDebugLine(
		GetWorld(),
		outLocation,
		lineTraceEnd,
		FColor(0, 255, 0), // green line
		false,
		0.f,
		0.f,
		5.f // pixel width
	);
}

