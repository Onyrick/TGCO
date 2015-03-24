#pragma once


/** 
* @namespace	ERailType  
* 				
* @brief Contain the list of rails' type
*/
namespace ERailType
{
	/**   
	* @enum	Type  
	* @brief List of Rail Type
	*/
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