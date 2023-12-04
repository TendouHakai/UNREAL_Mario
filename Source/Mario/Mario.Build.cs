// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Mario : ModuleRules
{
	public Mario(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D", "UMG"});
	}
}
