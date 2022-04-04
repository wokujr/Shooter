// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleEventManager.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	BaseTurnRate(45.f),
	BaseLookUpRate(50.f)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create camera boom(pulls in towards the character if there is a collision
	CameraBom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBom->SetupAttachment(RootComponent);
	CameraBom->TargetArmLength = 300.f; //camera will follow character at this length
	CameraBom->bUsePawnControlRotation = true; //when controller moves its gonna use that rotation

	// create follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBom, USpringArmComponent::SocketName); // attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; // camera doesnt rotate relative to arm


}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();


}

void AShooterCharacter::MoveForward(float Value)
{

	// Find out which way is forward
	if((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotator{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotator}.GetUnitAxis(EAxis::X) };
		AddMovementInput(Direction, Value);

	}

}

void AShooterCharacter::MoveRight(float Value)
{
	// Find out which way is Right
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotator{ 0, Rotation.Yaw, 0 };

		const FVector Direction{ FRotationMatrix{YawRotator}.GetUnitAxis(EAxis::Y) };
		AddMovementInput(Direction, Value);

	}

}

void AShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds()); // BaseTurnRate aka deg/sec * frame/sec aka GetWorld->GetDeltaSeconds 

}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this from rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds()); // deg/sec * frame/sec
}



// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

