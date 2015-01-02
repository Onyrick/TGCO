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

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
