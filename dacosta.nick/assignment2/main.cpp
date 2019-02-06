/**********************************************************************
**		Author: Nick DaCosta										 **
**		Class: 310 <Section 01>										 **
**		Assignment: pa 2											 **
**		Certification of Authenticity:								 **
**		I certify that this assignment is entirely my own work.	     **
**********************************************************************/
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string>
#include <time.h>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsSystem.h"


/*****************************************************************************************************************************
**													INSTRUCTIONS															**
**																															**
**	[X] Create and initialize GraphicsSystem object 800x600																	**
**	[X] Create 3 GraphicsBuffers (steps, smurfs, red (800x600) from memory)													**
**	[X] Fill red with words "Curse you Papa Smurf!" in black GraphicsSystem::writeText() writes to target graphics buffer	**
**	[X] Draw all red buffer																									**
**	[X] Scale steps buffer by 1/3 and center in red buffer																	**
**	[X] Create 16 smurf sprites (1 each from spritesheet) at random locations												**
**	[X] Save the Back Buffer to backbuffer.jpg using GraphicsSystem::saveBuffer()											**
**	[X] Save the RedBuffer with text to redbuffer.jpg using GraphicsSystem::saveBuffer()									**
**	[X] Flip the display																									**
**	[X] Close display gracefully after 5 seconds																			**
*****************************************************************************************************************************/

// Display dimensions.
const int DISPLAY_WIDTH  = 800;
const int DISPLAY_HEIGHT = 600;

// Asset locations and names.
const std::string ASSET_PATH            = "..\\..\\shared\\assets\\";
const std::string RED_BUFFER_FILENAME   = "redbuffer.jpg";
const std::string BACK_BUFFER_FILENMAE  = "backbuffer.jpg";
const std::string SMURF_SPRITE_FILENAME = "smurf_sprites.png";
const std::string STEPS_BITMAP_FILENAME = "steps.png";
const std::string FONT_FILENAME         = "cour.ttf";
const std::string SMURF_MESSAGE         = "Curse you Papa Smurf!";

const int FONT_SIZE                = 40;
const int SPRITESHEET_ROW_COUNT    = 4;
const int SPRITESHEET_COLUMN_COUNT = 4;

const float TEXT_X = 50;
const float TEXT_Y = 50;

const float STEPS_BITMAP_SCALE = 0.33f;

const Color RED_COLOR   = Color(255, 0, 0);
const Color BLACK_COLOR = Color(0,   0, 0);

const double SLEEP_TIME = 5.0;


int main()
{
	// Create a random seed for number generation.
	srand(time(NULL));

	// Create a performance tracker.
	PerformanceTracker* pPerformanceTracker = new PerformanceTracker;

	/*********************
		Tracker names.
	**********************/
	const std::string INIT_TRACKER_NAME = "init";
	const std::string DRAW_TRACKER_NAME = "draw";
	const std::string WAIT_TRACKER_NAME = "wait";

	// Start tracking the initialization.
	pPerformanceTracker->startTracking(INIT_TRACKER_NAME);

	// Create graphics system with 800x600 display.
	GraphicsSystem graphicsSystem = GraphicsSystem();

	// Initalize the graphics system.
	graphicsSystem.initialize(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// Stop tracking initialization.
	pPerformanceTracker->stopTracking(INIT_TRACKER_NAME);

	// Start tracking drawing.
	pPerformanceTracker->startTracking(DRAW_TRACKER_NAME);

	// Create steps graphics buffer.
	GraphicsBuffer stepsBuffer = GraphicsBuffer(ASSET_PATH, STEPS_BITMAP_FILENAME);

	// Create smurfs graphics buffer.
	GraphicsBuffer smurfsBuffer = GraphicsBuffer(ASSET_PATH, SMURF_SPRITE_FILENAME);

	// Create red graphics buffer.
	GraphicsBuffer redBuffer = GraphicsBuffer(DISPLAY_WIDTH, DISPLAY_HEIGHT, RED_COLOR);

	// Create a new font.
	Font courrierFont = Font(ASSET_PATH, FONT_FILENAME, FONT_SIZE);
	
	// Draw text to the red buffer in black "Curse you Papa Smurf!".
	graphicsSystem.writeText(redBuffer, TEXT_X, TEXT_Y, courrierFont, BLACK_COLOR, SMURF_MESSAGE);

	// Save the red buffer to redbuffer.jpg.
	graphicsSystem.saveBuffer(redBuffer, RED_BUFFER_FILENAME);

	// Draw the red buffer.
	graphicsSystem.draw(redBuffer);

	// Draw the steps buffer on the red buffer scaled by 1/3.
	graphicsSystem.draw(stepsBuffer, STEPS_BITMAP_SCALE);

	// Create an array to store each sprite.
	Sprite smurfSprites [SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT];

	// Calculate the sprite width.
	int spriteWidth = smurfsBuffer.getWidth() / SPRITESHEET_COLUMN_COUNT;

	// Calculate the sprite height.
	int spriteHeight = smurfsBuffer.getHeight() / SPRITESHEET_ROW_COUNT;

	// Create a separate sprite for each one on the sheet.
	for (int spriteRow = 0; spriteRow < SPRITESHEET_COLUMN_COUNT; spriteRow++)
	{
		for (int spriteColumn = 0; spriteColumn < SPRITESHEET_COLUMN_COUNT; spriteColumn++)
		{
			smurfSprites[spriteRow * SPRITESHEET_ROW_COUNT + spriteColumn] = Sprite(&smurfsBuffer, spriteWidth * spriteColumn, spriteHeight * spriteRow, spriteWidth, spriteHeight);
		}
	}

	// Randomly draw each sprite on the buffer.
	for (int currentSprite = 0; currentSprite < SPRITESHEET_COLUMN_COUNT * SPRITESHEET_ROW_COUNT; currentSprite++)
	{
		float destinationX = rand() % (graphicsSystem.getWidth() - spriteWidth) + 1;
		float destinationY = rand() % (graphicsSystem.getHeight() - spriteHeight) + 1;

		graphicsSystem.draw(smurfSprites[currentSprite], destinationX, destinationY);
	}

	// Save the back buffer to backbuffer.jpg.
	graphicsSystem.saveBuffer(graphicsSystem.getBackBuffer(), BACK_BUFFER_FILENMAE);

	// Update the display.
	graphicsSystem.updateDisplay();

	// Stop tracking drawing.
	pPerformanceTracker->stopTracking(DRAW_TRACKER_NAME);

	// Start tracking waiting.
	pPerformanceTracker->startTracking(WAIT_TRACKER_NAME);

	/******************
		Wait timer.
	*******************/
	Timer* pTimer = new Timer;
	pTimer->start();
	pTimer->sleepUntilElapsed(SLEEP_TIME*1000.0);

	// Stop tracking waiting.
	pPerformanceTracker->stopTracking(WAIT_TRACKER_NAME);

	// Clean up the system.
	graphicsSystem.cleanUp();

	/****************************
		Report elapsed times.
	*****************************/
	std::cout << "Time to Init:" << pPerformanceTracker->getElapsedTime(INIT_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time to Draw:" << pPerformanceTracker->getElapsedTime(DRAW_TRACKER_NAME) << " ms" << std::endl;
	std::cout << "Time spent waiting:" << pPerformanceTracker->getElapsedTime(WAIT_TRACKER_NAME) << " ms" << std::endl;

	// Delete pTimer and pPerformanceTracker to free up memory.
	delete pTimer;
	delete pPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations(std::cout);
	system("pause");

	return 0;

}