
#pragma once

/**
* @namespace	ERainbowBoxColor
*
* @brief	Contain the enum of rainbow box color
*/
namespace ERainbowBoxColor
{
	/**
	* @enum	Color
	*
	* @brief	List of color
	*/
	enum Color
	{
		NONE,
		RED,  
		GREEN, 
		BLUE
	};
}

/**
* Return the red value of the color
*
* @param SolutionType value of the enum ERainbowBoxColor
* @return float red value of the color
*/
float GetRedValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor);

/**
* Return the green value of the color
*
* @param SolutionType value of the enum ERainbowBoxColor
* @return float green value of the color
*/
float GetGreenValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor);

/**
* Return the blue value of the color
*
* @param SolutionType value of the enum ERainbowBoxColor
* @return float blue value of the color
*/
float GetBlueValueOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor);

/**
* Return the blue name of the color
*
* @param SolutionType value of the enum ERainbowBoxColor
* @return FName name of the color
*/
FName GetNameOfTheColor(const ERainbowBoxColor::Color RainbowBoxColor);

/**
* Return the color from a int
*
* @param iColor Int of the color
* @return ERainbowBoxColor::Color The corresponding Color
*/
ERainbowBoxColor::Color GetColorFromInt(int iColor);

/**
* Return the int from a color
*
* @param RainbowBoxColor The color
* @return int The corresponding int
*/
int GetIntFromColor(ERainbowBoxColor::Color RainbowBoxColor);
