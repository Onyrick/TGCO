#pragma once

namespace ERailType
{
	/** List of Rail Type */
	enum Type
	{
		STRAIGHT,
		CURVE
	};
}

/**
* Return the name of the rail type
*
* @param RailType value of the enum ERailType
*
* @return FString string of the rail type
*/
FString GetNameOfTheRail(const ERailType::Type RailType);