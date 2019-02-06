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

#include "Trackable.h"

#include <iostream>

#include "Color.h"

/// <summary>
///		Holds a chunk of memory to display something.
/// </summary>
/// <seealso cref="PerformanceTracker" />
class GraphicsBuffer : 
	public Trackable
{
public:
	// Basic buffer constructor.
	GraphicsBuffer();

	// Constructor taking in an allegro bitmap.
	GraphicsBuffer(ALLEGRO_BITMAP* _pBitmap);

	// Load a buffer from a file.
	GraphicsBuffer(std::string _readPath, std::string fileName);
	
	// Create a buffer with a given dimension and a color applied to it.
	GraphicsBuffer(int _width, int _height, Color _color);

	// Clean up the instance of the buffer.
	~GraphicsBuffer();

	// Initialize the required components.
	void initialize();

	// Get the height of the buffer.
	int getHeight();

	// Get the width of the buffer.
	int getWidth();

	friend class GraphicsSystem;

private:
	// Allegro bitmap.
	ALLEGRO_BITMAP* mpBitmap = nullptr;

	// Check if this class owns the bitmap pointer or not.
	bool mOwnsBitmap = false;
};