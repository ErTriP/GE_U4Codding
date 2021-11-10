// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GE_UECodding : ModuleRules
{
	public GE_UECodding(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
