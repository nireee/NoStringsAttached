/*******************************************************************************
The content of this file includes portions of the proprietary AUDIOKINETIC Wwise
Technology released in source code form as part of the game integration package.
The content of this file may not be used without valid licenses to the
AUDIOKINETIC Wwise Technology.
Note that the use of the game engine is subject to the Unreal(R) Engine End User
License Agreement at https://www.unrealengine.com/en-US/eula/unreal

License Usage

Licensees holding valid licenses to the AUDIOKINETIC Wwise Technology may use
this file in accordance with the end user license agreement provided with the
software or, alternatively, in accordance with the terms contained
in a written agreement between you and Audiokinetic Inc.
Copyright (c) 2023 Audiokinetic Inc.
*******************************************************************************/

/*=============================================================================
	AkReverbZone.cpp:
=============================================================================*/

#include "AkReverbZone.h"

AAkReverbZone::AAkReverbZone(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	// Set default values
	Room->WallOcclusion = 0;
	SurfaceReflectorSet->bEnableSurfaceReflectors = false;
}

void AAkReverbZone::UpdateParentSpatialAudioVolume(AAkSpatialAudioVolume* InParentSpatialAudioVolume)
{
	if (ParentSpatialAudioVolume != InParentSpatialAudioVolume)
	{
		ParentSpatialAudioVolume = InParentSpatialAudioVolume;
		bReverbZoneNeedsUpdate = true;
	}
}

void AAkReverbZone::UpdateTransitionRegionWidth(float InTransitionRegionWidth)
{
	if (InTransitionRegionWidth < 0.f)
		InTransitionRegionWidth = 0.f;

	if (TransitionRegionWidth != InTransitionRegionWidth)
	{
		TransitionRegionWidth = InTransitionRegionWidth;
		bReverbZoneNeedsUpdate = true;
	}
}

void AAkReverbZone::BeginPlay()
{
	Super::BeginPlay();

	SetReverbZone();
}

void AAkReverbZone::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Room == nullptr)
	{
		return;
	}

	Room->RemoveReverbZone();
}

void AAkReverbZone::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bReverbZoneNeedsUpdate)
	{
		SetReverbZone();
		bReverbZoneNeedsUpdate = false;
	}
}

#if WITH_EDITOR
void AAkReverbZone::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName memberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr) ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None;

	if (memberPropertyName == GET_MEMBER_NAME_CHECKED(AAkReverbZone, ParentSpatialAudioVolume))
	{
		bReverbZoneNeedsUpdate = true;
	}
	if (memberPropertyName == GET_MEMBER_NAME_CHECKED(AAkReverbZone, TransitionRegionWidth))
	{
		if (TransitionRegionWidth < 0.f)
			TransitionRegionWidth = 0.f;

		bReverbZoneNeedsUpdate = true;
	}
}
#endif

void AAkReverbZone::SetReverbZone()
{
	if (Room == nullptr || (Room && !Room->bEnable))
	{
		UE_LOG(LogAkAudio, Error, TEXT("AkReverbZone %s: child Room component is not enabled. A Reverb Zone needs to be a Spatial Audio Room."), *GetName());
		return;
	}

	UAkRoomComponent* ParentRoomComponent = nullptr;
	if (ParentSpatialAudioVolume != nullptr)
	{
		if (ParentSpatialAudioVolume->Room == nullptr || (ParentSpatialAudioVolume->Room && !ParentSpatialAudioVolume->Room->bEnable))
		{
			UE_LOG(LogAkAudio, Error, TEXT("AkReverbZone %s: child Room component of the parent Spatial Audio Volume %s is not enabled. A Reverb Zone needs a Parent Spatial Audio Room."), *GetName(), *ParentSpatialAudioVolume->GetName());
			return;
		}
		else
		{
			ParentRoomComponent = ParentSpatialAudioVolume->Room;
		}
	}

	Room->SetReverbZone(ParentRoomComponent, TransitionRegionWidth);
}

AkRoomID AAkReverbZone::GetParentRoomID()
{
	AkRoomID ParentRoomID = AK::SpatialAudio::kOutdoorRoomID;
	if (ParentSpatialAudioVolume != nullptr && ParentSpatialAudioVolume->Room != nullptr)
	{
		ParentRoomID = ParentSpatialAudioVolume->Room->GetRoomID();
	}

	return ParentRoomID;
}
