// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TGCO : ModuleRules
{
	public TGCO(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(
            new string[] { 
				"TGCO/Private", 
            }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] { 
                "Core", 
                "CoreUObject", 
                "Engine", 
                "InputCore",
                "OnlineSubsystem",
				"OnlineSubsystemUtils",
                "AIModule", 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "OnlineSubsystem",
            }
        );

        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.Mac))
        {
            if (UEBuildConfiguration.bCompileSteamOSS == true)
            {
                DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
            }

            DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        }
	}
}
