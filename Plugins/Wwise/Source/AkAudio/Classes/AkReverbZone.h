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
	AkReverbZone.h:
=============================================================================*/
#pragma once

#include "AkSpatialAudioVolume.h"
#include "AkReverbZone.generated.h"


/*------------------------------------------------------------------------------------
	AAkSpatialAudioVolume
------------------------------------------------------------------------------------*/
UCLASS(ClassGroup = Audiokinetic, BlueprintType, hidecategories = (Advanced, Attachment, Volume))
class AKAUDIO_API AAkReverbZone : public AAkSpatialAudioVolume
{
	GENERATED_BODY()

public:
	AAkReverbZone(const class FObjectInitializer& ObjectInitializer);

	/**
	* Establishes a parent-child relationship between two Rooms and allows for sound propagation between them
	* as if they were the same Room, without the need for a connecting Portal.
	* A parent Room may have multiple Reverb Zones, but a Reverb Zone can only have a single Parent.
	* The Reverb Zone and its parent are both Rooms, and as such, must be specified using Enable Room.
	* The automatically created 'outdoors' Room is commonly used as a parent Room for Reverb Zones, since they often model open spaces.
	* To attach a Reverb zone to outdoors, leave this property to None.
	*/
	UPROPERTY(EditAnywhere, BlueprintSetter = UpdateParentSpatialAudioVolume, Category = "ReverbZone")
	AAkSpatialAudioVolume* ParentSpatialAudioVolume = nullptr;

	/** Set ParentSpatialAudioVolume with a new volume and notify updating the Reverb Zone in Wwise. */
	UFUNCTION(BlueprintSetter, Category = "ReverbZone")
	void UpdateParentSpatialAudioVolume(AAkSpatialAudioVolume* InParentSpatialAudioVolume);

	/**
	* Width of the transition region between the Reverb Zone and its parent.
	* The transition region is centered around the Reverb Zone geometry. It only applies where surface transmission loss is set to 0.
	* The value must be positive. Negative values are treated as 0.
	*/
	UPROPERTY(EditAnywhere, BlueprintSetter = UpdateTransitionRegionWidth, Category = "ReverbZone")
	float TransitionRegionWidth = 0.f;

	/** Set TransitionRegionWidth with a new value and notify updating the Reverb Zone in Wwise. */
	UFUNCTION(BlueprintSetter, Category = "ReverbZone")
	void UpdateTransitionRegionWidth(float InTransitionRegionWidth);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void SetReverbZone();
	AkRoomID GetParentRoomID();

	bool bReverbZoneNeedsUpdate = false;

};
