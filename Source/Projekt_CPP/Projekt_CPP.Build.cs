// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projekt_CPP : ModuleRules
{
	public Projekt_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Projekt_CPP",
			"Projekt_CPP/Variant_Platforming",
			"Projekt_CPP/Variant_Platforming/Animation",
			"Projekt_CPP/Variant_Combat",
			"Projekt_CPP/Variant_Combat/AI",
			"Projekt_CPP/Variant_Combat/Animation",
			"Projekt_CPP/Variant_Combat/Gameplay",
			"Projekt_CPP/Variant_Combat/Interfaces",
			"Projekt_CPP/Variant_Combat/UI",
			"Projekt_CPP/Variant_SideScrolling",
			"Projekt_CPP/Variant_SideScrolling/AI",
			"Projekt_CPP/Variant_SideScrolling/Gameplay",
			"Projekt_CPP/Variant_SideScrolling/Interfaces",
			"Projekt_CPP/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
