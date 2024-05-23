// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class _change_project_name_ : ModuleRules
{
    public _change_project_name_(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AnimGraph", "AnimGraphRuntime", "BlueprintGraph", "NavigationSystem", "AIModule" });

        PublicAdditionalLibraries.Add(Path.Combine(ProjectRoot, "Binaries/Win64/Kinect20.lib"));
    }

    public string ProjectRoot
    {
        get { return System.IO.Path.GetFullPath(System.IO.Path.Combine(ModuleDirectory, "../../")); }
    }


}
