// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WheelOfTime : ModuleRules
{
	public WheelOfTime(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{ 
			"GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks",
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"NavigationSystem",
			"AIModule", 
			"Niagara",
			"EnhancedInput",
			"UMG", 
			"Slate", 
			"SlateCore"
        });
	}
}
