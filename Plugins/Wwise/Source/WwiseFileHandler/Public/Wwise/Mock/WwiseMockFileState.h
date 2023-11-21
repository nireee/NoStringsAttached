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

#pragma once

#include "Wwise/WwiseFileState.h"

class FWwiseMockFileState : public FWwiseFileState
{
public:
	const TCHAR* GetManagingTypeName() const override final { return TEXT("Test"); }
	uint32 GetShortId() const override final { return ShortId; }

	FWwiseMockFileState(uint32 ShortId) :
		ShortId(ShortId)
	{}
	~FWwiseMockFileState() override { Term(); }

	void OpenFile(FOpenFileCallback&& InCallback) override
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, InCallback = MoveTemp(InCallback)]() mutable
		{
			if (bOpenFileSuccess)
			{
				OpenFileSucceeded(MoveTemp(InCallback));
			}
			else
			{
				OpenFileFailed(MoveTemp(InCallback));
			}
		});
	}
	
	void LoadInSoundEngine(FLoadInSoundEngineCallback&& InCallback) override
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, InCallback = MoveTemp(InCallback)]() mutable
		{
			if (bLoadInSoundEngineSuccess)
			{
				LoadInSoundEngineSucceeded(MoveTemp(InCallback));
			}
			else
			{
				LoadInSoundEngineFailed(MoveTemp(InCallback));
			}
		});
	}
	void UnloadFromSoundEngine(FUnloadFromSoundEngineCallback&& InCallback) override
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, InCallback = MoveTemp(InCallback)]() mutable
		{
			if (bUnloadFromSoundEngineDefer)
			{
				UnloadFromSoundEngineDefer(MoveTemp(InCallback));
			}
			else
			{
				UnloadFromSoundEngineDone(MoveTemp(InCallback));
			}
		});
	}
	void CloseFile(FCloseFileCallback&& InCallback) override
	{
		FFunctionGraphTask::CreateAndDispatchWhenReady([this, InCallback = MoveTemp(InCallback)]() mutable
		{
			if (bCloseFileDefer)
			{
				CloseFileDefer(MoveTemp(InCallback));
			}
			else
			{
				CloseFileDone(MoveTemp(InCallback));
			}
		});
	}

	enum class OptionalBool
	{
		False,
		True,
		Default
	};

	bool CanDelete() const override { return bCanDelete == OptionalBool::Default ? FWwiseFileState::CanDelete() : bCanDelete == OptionalBool::False ? false : true; }
	bool CanOpenFile() const override { return bCanOpenFile == OptionalBool::Default ? FWwiseFileState::CanOpenFile() : bCanOpenFile == OptionalBool::False ? false : true; }
	bool CanLoadInSoundEngine() const override { return bCanLoadInSoundEngine == OptionalBool::Default ? FWwiseFileState::CanLoadInSoundEngine() : bCanLoadInSoundEngine == OptionalBool::False ? false : true; }
	bool CanUnloadFromSoundEngine() const override { return bCanUnloadFromSoundEngine == OptionalBool::Default ? FWwiseFileState::CanUnloadFromSoundEngine() : bCanUnloadFromSoundEngine == OptionalBool::False ? false : true; }
	bool CanCloseFile() const override { return bCanCloseFile == OptionalBool::Default ? FWwiseFileState::CanCloseFile() : bCanCloseFile == OptionalBool::False ? false : true; }
	bool IsStreamedState() const override { return bIsStreamedState == OptionalBool::Default ? FWwiseFileState::IsStreamedState() : bIsStreamedState == OptionalBool::False ? false : true; }
	
	uint32 ShortId;
	bool bOpenFileSuccess{ true };
	bool bLoadInSoundEngineSuccess{ true };
	bool bUnloadFromSoundEngineDefer{ false };
	bool bCloseFileDefer{ false };

	OptionalBool bCanDelete{ OptionalBool::Default };
	OptionalBool bCanOpenFile{ OptionalBool::Default };
	OptionalBool bCanLoadInSoundEngine{ OptionalBool::Default };
	OptionalBool bCanUnloadFromSoundEngine{ OptionalBool::Default };
	OptionalBool bCanCloseFile{ OptionalBool::Default };
	OptionalBool bIsStreamedState{ OptionalBool::Default };
};
