// Fill out your copyright notice in the Description page of Project Settings.


#include "Puppy.h"

// Sets default values
APuppy::APuppy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuppy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuppy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuppy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APuppy::PuppyMove()
{

}
