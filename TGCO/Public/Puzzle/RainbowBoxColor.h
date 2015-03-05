

#pragma once


namespace ERainbowBoxColor
{
	/** List of solution type */
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

/** Convert a int to a RainbowBoxColor */
ERainbowBoxColor::Color GetColorFromInt(int iColor);

/** Convert a RainbowBoxColor to a int */
int GetIntFromColor(ERainbowBoxColor::Color RainbowBoxColor);
