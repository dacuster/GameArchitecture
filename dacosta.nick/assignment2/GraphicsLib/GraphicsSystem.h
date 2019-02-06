/**********************************************************************
**		Author: Nick DaCosta										 **
**		Class: 310 <Section 01>										 **
**		Assignment: pa 2											 **
**		Certification of Authenticity:								 **
**		I certify that this assignment is entirely my own work.	     **
**********************************************************************/
#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <iostream>

#include "Font.h"
#include "Color.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"

/// <summary>
///		Creates and maintains the display.
/// </summary>
/// <seealso cref="PerformanceTracker" />
class GraphicsSystem :
	public Trackable
{
public:
	// Create default graphics system.
	GraphicsSystem();

	// Destroy the display pointer.
	~GraphicsSystem();

	// TODO: GraphicsSystem initialize (don't call from constructor).
	void initialize(int _width, int _height);

	// TODO: Clean up the allegro system.
	void cleanUp();

	// TODO: Get the width of the display.
	int getWidth();

	// TODO: Get the height of the display.
	int getHeight();

	// TODO: Bring the back buffer to the main buffer.
	void updateDisplay();

	// TODO: Draw sprites.
	static void draw(Sprite _sprite, float _destinationX, float _destinationY, float _scale = 1.0);

	// TODO: Draw to back buffer.
	static void draw(GraphicsBuffer& _buffer, float _scale = 1.0f);

	// TODO: Write text to the current back buffer.
	static void writeText(float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text);

	// TODO: Write text to the given buffer.
	static void writeText(GraphicsBuffer& _buffer, float _destinationX, float _destinationY, Font& _font, Color _color, std::string _text);

	// TODO: Save the buffer as a jpg.
	static void saveBuffer(GraphicsBuffer& _buffer, std::string _fileName);

	// TODO: Get the back buffer of the display.
	GraphicsBuffer getBackBuffer();

private:
	// TODO: GraphicsSystem member variable allegro display.
	ALLEGRO_DISPLAY* mpDisplay;
};