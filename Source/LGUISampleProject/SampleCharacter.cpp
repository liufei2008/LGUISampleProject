// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ASampleCharacter::ASampleCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASampleCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASampleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASampleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis(moveForwardAxisName, this, &ASampleCharacter::MoveForward);
	PlayerInputComponent->BindAxis(moveRightAxisName, this, &ASampleCharacter::MoveRight);
	PlayerInputComponent->BindAxis(moveUpAxisName, this, &ASampleCharacter::MoveUp);
	PlayerInputComponent->BindAction(moveSpeedUpAxisName, IE_Pressed, this, &ASampleCharacter::MoveSpeedUp);
	PlayerInputComponent->BindAction(moveSpeedUpAxisName, IE_Released, this, &ASampleCharacter::MoveSpeedDown);
	PlayerInputComponent->BindAction(yawAndPitchActionName, IE_Pressed, this, &ASampleCharacter::BeginYawAndPitch);
	PlayerInputComponent->BindAction(yawAndPitchActionName, IE_Released, this, &ASampleCharacter::EndYawAndPitch);
	PlayerInputComponent->BindAxis(mouseXAxisName, this, &ASampleCharacter::Yaw);
	PlayerInputComponent->BindAxis(mouseYAxisName, this, &ASampleCharacter::Pitch);
}


void ASampleCharacter::MoveForward(float amount)
{
	auto forwardVector = MainCamera->GetForwardVector();
	forwardVector.Z = 0;
	forwardVector.Normalize();
	Move(forwardVector, amount);
}
void ASampleCharacter::MoveRight(float amount)
{
	Move(MainCamera->GetRightVector(), amount);
}
void ASampleCharacter::MoveUp(float amount)
{
	Move(FVector(0, 0, 1), amount);
}
void ASampleCharacter::Move(FVector direction, float amount)
{
	amount *= moveSpeed;
	if (amount)
	{
		auto location = MainCamera->GetComponentLocation();
		location += direction * amount;
		MainCamera->SetWorldLocation(location);
	}
}
void ASampleCharacter::Yaw(float amount)
{
	if (rightMouseButtonDown && (amount != 0))
	{
		auto rotation = MainCamera->RelativeRotation;
		rotation.Yaw += mouseXSensitivity * amount;
		MainCamera->SetRelativeRotation(rotation);
	}
}
void ASampleCharacter::Pitch(float amount)
{
	if (rightMouseButtonDown && (amount != 0))
	{
		auto rotation = MainCamera->RelativeRotation;
		rotation.Pitch += mouseYSensitivity * amount;
		rotation.Pitch = FMath::Clamp(rotation.Pitch, pitchAngleMin, pitchAngleMax);
		MainCamera->SetRelativeRotation(rotation);
	}
}