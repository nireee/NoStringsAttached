// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineComponent.h"

#include "Engine.h"

UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UStateMachineComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeStateMachine();
}


void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (canTickState && currentState->canTickState)
	{
		currentState->TickState();
	}
	
}


void UStateMachineComponent::ChangeState(UStateBase* i_newState)
{
	if (i_newState->IsValidLowLevel())
	{
		// If there is no current state, it means we are at init
		if (!currentState)
			currentState = i_newState;
		else
		{
			if (currentState->GetClass() == i_newState->GetClass())
			{
				GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, "StateMachine: Error: Trying to enter same state!");
				return;
			}

			canTickState = false;

			currentState->ExitState();

			currentState = i_newState;

			currentState->EnterState();

			canTickState = true;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, "StateMachine: Error: Switch failed. Invalid state!");
	}
}


void UStateMachineComponent::ChangeStateByName(FString i_stateName)
{
	UStateBase* newState = stateMap.FindRef(i_stateName);
	ChangeState(newState);
}


UStateBase* UStateMachineComponent::GetCurrentState()
{
	return currentState;
}


FString UStateMachineComponent::GetCurrentStateName()
{
	const FString* stateName = stateMap.FindKey(currentState);
	return *stateName;
}


void UStateMachineComponent::InitializeStateMachine()
{
	// Store the reference of the owner game object
	ownerObject = GetOwner();

	// Load all states into state machine
	for (auto iter = stateConfigs.CreateConstIterator(); iter; ++iter)
	{
		UStateBase* state = NewObject<UStateBase>(this, iter->Value);
		
		state->InitializeState(ownerObject);
		
		stateMap.Add(iter->Key, state);
	}

	// Set current state to initialState
	ChangeStateByName(initialState);
}




