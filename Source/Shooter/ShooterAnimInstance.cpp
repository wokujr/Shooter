// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UShooterAnimInstance::UpdateAnimationInstance(float DeltaTime)
{
	// check if ShooterCharacter point to null or not if yes we gonna try to cast it again
	if (ShooterCharacter == nullptr) 
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}
	if (ShooterCharacter)
	{
		//get lateral speed of the character
		FVector Velocity{ ShooterCharacter->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		// is the character in air?
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

		// is the character Accelerating ?
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;

		}
		else
		{
			bIsAccelerating = false;
		}
	}

}


void UShooterAnimInstance::NativeInitializeAnimation()
{
	//need to cast it to ShooterCharacter so include the ShooterCharacter.h then cast it here
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner()); 
}
