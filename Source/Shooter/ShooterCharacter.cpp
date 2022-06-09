// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	BaseTurnRate(45.f),
	BaseLookUpRate(45.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a camara boom (pulls in towards the character if there is a collision)
	CamaraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CamaraBoom"));
	CamaraBoom->SetupAttachment(RootComponent);
	CamaraBoom->TargetArmLength = 300.f; //The camara follows at this distance behind th character
	CamaraBoom->bUsePawnControlRotation = true; //Rotate the armvased on the controller

	//Create FollowCamara
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamara"));
	FollowCamera->SetupAttachment(CamaraBoom, USpringArmComponent::SocketName); //Attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = false; //Camara does not rotate relative to arm

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShooterCharacter::MoveForward(float Value)
{
	const FRotator Rotation{ Controller->GetControlRotation() };
	const FRotator YawRotation{ 0.f, Rotation.Yaw, 0.f };

	const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X) };
	AddMovementInput(Direction, Value);
}

void AShooterCharacter::MoveRight(float Value)
{
	const FRotator Rotation{ Controller->GetControlRotation() };
	const FRotator YawRotation{ 0.f, Rotation.Yaw, 0.f };

	const FVector Direction{ FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y) };

	AddMovementInput(Direction, Value);
}

void AShooterCharacter::TurnRate(float Rate)
{
	//Calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
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
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
}

