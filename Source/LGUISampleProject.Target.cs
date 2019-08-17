// Copyright 2018 LexLiu. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LGUISampleProjectTarget : TargetRules
{
	public LGUISampleProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "LGUISampleProject" } );
	}
}
