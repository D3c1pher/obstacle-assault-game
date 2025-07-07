// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	FString Name = GetName();
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);

	/** Sample Output Log Code **/
	// UE_LOG(LogTemp, Display, TEXT("THIS IS A DISPLAY MESSAGE!"));
	// UE_LOG(LogTemp, Warning, TEXT("THIS IS A WARNING MESSAGE!"));
	// UE_LOG(LogTemp, Error, TEXT("THIS IS AN ERROR MESSAGE!"));
	// UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MoveDistance);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/** Sample Code **/
	// FVector LocalVector = MyVector;
	// LocalVector.Z = LocalVector.Z + 100;
	// MyVector.Y = MyVector.Y + 1;
	// SetActorLocation(LocalVector);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		/**Old Code for Sample Output Log**/
		// float OverShoot = DistanceMoved - MoveDistance;
		// FString Name = GetName();
		// UE_LOG(LogTemp, Display, TEXT("%s Platform overshot by %f"), *Name, OverShoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else 
	{
		FVector CurrentLocation = GetActorLocation(); 
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	/** Imperfect solution **/
	// FRotator CurrentRotation = GetActorRotation();
	// CurrentRotation += RotationVelocity * DeltaTime;
	// SetActorRotation(CurrentRotation);

	AddActorLocalRotation(RotationVelocity * DeltaTime); // Proper Solution
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() >= MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}
