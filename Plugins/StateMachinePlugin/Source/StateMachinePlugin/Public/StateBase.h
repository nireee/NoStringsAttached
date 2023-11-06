// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "StateBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STATEMACHINEPLUGIN_API UStateBase : public UObject
{
	GENERATED_BODY()
	

	// Interface 
	//====================================

public:

	void InitializeState(AActor* i_ownerObject);

	void EnterState();

	void TickState();

	void ExitState();

	UFUNCTION(BlueprintImplementableEvent, Category = "StateBase")
	void EnterStateEvent_Blueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "StateBase")
	void TickStateEvent_Blueprint();

	UFUNCTION(BlueprintImplementableEvent, Category = "StateBase")
	void ExitStateEvent_Blueprint();

	virtual void EnterStateEvent_CPP();

	virtual void TickStateEvent_CPP();

	virtual void ExitStateEvent_CPP();


	// Data 
	//====================================

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	bool canTickState = true;

	//UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "State Machine")
	//AActor* ownerObject = nullptr;

};
