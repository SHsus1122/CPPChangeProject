// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TempNameProject : ModuleRules
{
	public TempNameProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "MainSoundPlugin", "HomeLevelGameModePlugin", "UMG", "EnhancedInput", "IntroPlugin", "WASDEnhancedInput", "Sockets", "Networking", "OnlineSubsystem", "OnlineSubsystemUtils", "ChatPlugin", "Home" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        PublicIncludePaths.AddRange(new string[] { "TempNameProject" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
