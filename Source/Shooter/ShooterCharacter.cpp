// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
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

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

