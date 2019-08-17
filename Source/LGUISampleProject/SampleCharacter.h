// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SampleCharacter.generated.h"

UCLASS()
class LGUISAMPLEPROJECT_API ASampleCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASampleCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Move)
		float moveSpeed = 1.0f;
	//float targetMoveSpeed = 1.0f;
	UPROPERTY(EditAnywhere, Category = Move)
		float moveSpeedMax = 3.0f;
	UPROPERTY(EditAnywhere, Category = Move)
		float moveSpeedMin = 1.0f;
	UPROPERTY(EditAnywhere, Category = Move)
		FName moveSpeedUpAxisName = TEXT("SpeedUp");
	UPROPERTY(EditAnywhere, Category = Move)
		FName moveForwardAxisName = TEXT("Forward");
	UPROPERTY(EditAnywhere, Category = Move)
		FName moveRightAxisName = TEXT("Right");
	UPROPERTY(EditAnywhere, Category = Move)
		FName moveUpAxisName = TEXT("Up");
	UPROPERTY(EditAnywhere, Category = Move)
		FName yawAndPitchActionName = TEXT("YawAndPitch");
	UPROPERTY(EditAnywhere, Category = Move)
		FName mouseXAxisName = TEXT("MouseX");
	UPROPERTY(EditAnywhere, Category = Move)
		FName mouseYAxisName = TEXT("MouseY");
	UPROPERTY(EditAnywhere, Category = Move)
		float mouseXSensitivity = 1;
	UPROPERTY(EditAnywhere, Category = Move)
		float mouseYSensitivity = 1;
	UPROPERTY(EditAnywhere, Category = Move)
		float pitchAngleMax = 80;
	UPROPERTY(EditAnywhere, Category = Move)
		float pitchAngleMin = -80;
	UPROPERTY(EditAnywhere, Category = Move)
		class ULGUIPrefab* testPrefab;

	bool rightMouseButtonDown = false;
	FQuat startRotation;

	void MoveForward(float amount);
	void MoveRight(float amount);
	void MoveUp(float amount);
	void Move(FVector direction, float amount);
	void MoveSpeedUp() { moveSpeed = moveSpeedMax; }
	void MoveSpeedDown() { moveSpeed = moveSpeedMin; }
	void BeginYawAndPitch() { rightMouseButtonDown = true; }
	void EndYawAndPitch() { rightMouseButtonDown = false; }
	void Yaw(float amount);
	void Pitch(float amount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* MainCamera;
	
};
