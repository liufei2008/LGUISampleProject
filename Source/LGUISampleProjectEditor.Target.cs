// Copyright 2018 LexLiu. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class LGUISampleProjectEditorTarget : TargetRules
{
	public LGUISampleProjectEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "LGUISampleProject" } );
	}
}
