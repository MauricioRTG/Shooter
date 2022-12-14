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

	/* Called for foward/backwards input*/
	void MoveForward(float Value);

	/* Called for side to side input*/
	void MoveRight(float Value);

	/* Called via input to turn at a given rate.
	* @param Rate: This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnRate(float Rate);

	/*
	* Called via input look up/down at a given rate.
	* @param Rate This a normalized rate, i.e. 1.0 means 100% of desired rate
	*/
	void LookUpAtRate(float Rate);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/* Camara boom positioning the camara behind the character*/
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camara, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CamaraBoom;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camara, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/* Base turn rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/* Base look up/down rate, in deg/sec. Other scaling may affect final turn rate */
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camara, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

public:
	/* Retruns CamaraBoom subobject */
	FORCEINLINE USpringArmComponent* GetCamaraBoom() const { return CamaraBoom; }

	/* Returns FollowCamara subobject */
	FORCEINLINE UCameraComponent* GetFollowCamara() const { return FollowCamera; }

};
