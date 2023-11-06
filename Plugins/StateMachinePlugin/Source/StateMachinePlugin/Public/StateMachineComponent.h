// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateBase.h"

#include "StateMachineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STATEMACHINEPLUGIN_API UStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()


	// Interface
	//====================================

public:	

	UStateMachineComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void ChangeState(UStateBase* i_newState);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void ChangeStateByName(FString i_stateName);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	UStateBase* GetCurrentState();

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	FString GetCurrentStateName();


	// Implementation
	//====================================

protected:

	// Called when the game starts
	virtual void BeginPlay() override;


private:

	void InitializeStateMachine();


	// Data
	//====================================

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "StateMachine")
	FString initialState;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "StateMachine")
	TMap<FString, TSubclassOf<UStateBase>> stateConfigs;


private:

	bool canTickState = false;

	TMap<FString, UStateBase*> stateMap;

	UStateBase* currentState = nullptr;

	AActor* ownerObject = nullptr;
};
