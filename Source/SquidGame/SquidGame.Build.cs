// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SquidGame : ModuleRules
{
	public SquidGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PrivateIncludePaths.Add("SquidGame");
	}
}
