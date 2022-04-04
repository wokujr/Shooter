// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backwards input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * called via input to turn at given rate
	 * @param Rate this a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * called via input to look UP/DOWN at given rate
	 * @param Rate this a normalized rate i.e. 1.0 means 100% of desired rate
	 */
	void LookUpAtRate(float Rate);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	/** Camera Boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere,	BlueprintReadOnly ,Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Base turn rate, in deg/sec. other scalling may affect turn rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. other scalling may affect look up/down rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

public:
	/** Return CameraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCameraBom() const { return CameraBom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }


};
