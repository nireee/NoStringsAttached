// Fill out your copyright notice in the Description page of Project Settings.


#include "StateBase.h"


void UStateBase::InitializeState(AActor* i_ownerObject)
{
	ownerObject = i_ownerObject;

	InitializeStateEvent_Blueprint();
	InitializeStateEvent_CPP();
}


void UStateBase::EnterState()
{
	EnterStateEvent_Blueprint();
	EnterStateEvent_CPP();
}


void UStateBase::TickState()
{
	TickStateEvent_Blueprint();
	TickStateEvent_CPP();
}


void UStateBase::ExitState()
{
	ExitStateEvent_Blueprint();
	ExitStateEvent_CPP();
}


void UStateBase::InitializeStateEvent_CPP()
{

}


void UStateBase::EnterStateEvent_CPP()
{

}


void UStateBase::TickStateEvent_CPP()
{

}


void UStateBase::ExitStateEvent_CPP()
{

}


AActor* UStateBase::GetOwnerObject()
{
	return this->ownerObject;
}
