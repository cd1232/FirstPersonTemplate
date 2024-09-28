#pragma once

#include "POIState.generated.h"

UENUM(BlueprintType)
enum class EPOIState : uint8
{
	Hidden,
	Visible,
	Active
};