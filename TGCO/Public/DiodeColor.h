
#pragma once

/**
* @namespace	EDiodeColor
*
* @brief	Contain the enum of diode's colors
*/
namespace EDiodeColor
{
	/**
	* @enum	Color
	*
	* @brief	List of the diode's colors
	*/
	enum Color
	{
		WHITE,
		RED,
		BLUE,
		GREEN,
		ORANGE
	};
}

/**
* Return the name of the diode color
*
* @param DiodeColor value of the enum EDiodeColor
*
* @return FString string of the  diode color
*/
FString GetColorOfTheDiode(const EDiodeColor::Color DiodeColor);