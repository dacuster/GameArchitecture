/*********************************************************************
**		Author:														**
**		Class: 310 <Section 0>										**
**		Assignment: pa 2											**
**		Certification of Authenticity:								**
**		I certify that this assignment is entirely my own work.	    **
**		Assingment 2 Author: Nick DaCosta							**
*********************************************************************/
#pragma once

#include "Trackable.h"

/// <summary>
/// 
/// </summary>
/// <seealso cref="PerformanceTracker" />
/// TODO Edit XML Comment Template for Color
class Color :
	public Trackable
{
public:
	// Initialize a default white color.
	Color();

	// Create a color with the given values.
	Color(int _r, int _g, int _b);

	// Clean up the color instance.
	~Color();

	// Get the red value.
	int getR();

	// Get the green value.
	int getG();

	// Get the blue value.
	int getB();

private:
	// Red
	int mR = 0;

	// Green
	int mG = 0;

	// Blue
	int mB = 0;

};