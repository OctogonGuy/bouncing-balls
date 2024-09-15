#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 400
#define BACKGROUND_COLOR 0xFFFFFF
#define NUM_BALLS 5
#define RADIUS_LOWER 5
#define RADIUS_UPPER 50
#define SPEED_LOWER 25.0
#define SPEED_UPPER 250.0

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>

#include "util.h"
#include "ball.h"

// SDL-related objects
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t last_time = 0;

// SDL-related functions
void _init_();
void _update_();
void _render_();
void _close_();

// Ball-related objects
Ball* balls[NUM_BALLS];

// Ball-related functions
Ball* newBall();
void deleteBall(Ball*);


int main(int argc, char** argv)
{
	// Initialize SDL
	_init_();

	// Game loop
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		_update_();
		_render_();
	}

	// Close SDL
	_close_();

	return 0;
}


void _init_()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize. %s\n", SDL_GetError());
	}

	// Create window
	window = SDL_CreateWindow(
			"Bouncing Balls",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created %s\n", SDL_GetError());
	}

	// Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created. %s\n", SDL_GetError());
	}

	// Seed pseudo-random number generator
	initRand();

	// Generate balls
	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i] = newBall();
	}
}


void _update_()
{
	// Calculate the number of ticks passed since last frame
	float now = SDL_GetTicks();
	float delta = now - last_time;
	last_time = now;

	// Move the collision circles of the balls
	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i]->move(delta, SCREEN_WIDTH, SCREEN_HEIGHT, balls, NUM_BALLS);
	}
}


void _render_()
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR>>(4*4)&0xFF, BACKGROUND_COLOR>>(2*4)&0xFF, BACKGROUND_COLOR>>(0*4)&0xFF, 1);
	SDL_RenderClear(renderer);

	// Render balls
	for (int i = 0; i < NUM_BALLS; i++)
	{
		balls[i]->render(renderer);
	}

	// Update screen
	SDL_RenderPresent(renderer);
}


void _close_()
{
	// Delete balls
	for (int i = 0; i < NUM_BALLS; i++)
	{
		deleteBall(balls[i]);
	}

	// Destroy resources
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();
}


Ball* newBall()
{
	// Generate random parameters
	int radius = randInt(RADIUS_LOWER, RADIUS_UPPER);
	float x = static_cast<int>(randInt(radius, SCREEN_WIDTH - radius));
	float y = static_cast<int>(randInt(radius, SCREEN_HEIGHT - radius));
	float speed = randFloat(SPEED_LOWER, SPEED_UPPER);
	float angle = randFloat(0.0f, 2*M_PI);
	uint8_t r = static_cast<uint8_t>(randInt(0, 255));
	uint8_t g = static_cast<uint8_t>(randInt(0, 255));
	uint8_t b = static_cast<uint8_t>(randInt(0, 255));

	// Construct ball
	Circle collider = { x, y, radius };
	Velocity velocity = { speed, angle };
	Color color = { r, g, b };
	Ball* ball = new Ball(collider, velocity, color);

	return ball;
}


void deleteBall(Ball* ball)
{
	delete ball;
}
