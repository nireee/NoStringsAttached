// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PuppyHero : ModuleRules
{
	public PuppyHero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
