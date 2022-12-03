// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class SGProtoBuf : ModuleRules
{
	public SGProtoBuf(ReadOnlyTargetRules Target) : base(Target)
	{
		//Type = ModuleType.External;
		
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		// Protobuf source integrationg

		//PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "lib"));
		//PublicSystemIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));

		ShadowVariableWarningLevel = WarningLevel.Off;
		bEnableUndefinedIdentifierWarnings = false;
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			bEnableExceptions = true;
		}
		PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
		PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
		//PublicDefinitions.Add("GOOGLE_PROTOBUF_CMAKE_BUILD");

		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotobuf.lib"));
		//Path.Combine(PluginDirectory, "Source/NetWork/ThirdParty/Protobuf/Lib/libprotobuf.lib");
	}
}
