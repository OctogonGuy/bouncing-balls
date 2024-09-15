#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include <SDL2/SDL.h>


// Circle
struct Circle
{
	float x, y;
	int radius;
};


// Velocity
struct Velocity
{
	float speed;	// pixels/second
	float angle;	// radians
};


// Color
struct Color
{
	uint8_t r, g, b;
};


class Ball
{
	public:
		// Constructor
		Ball(const Circle& collider, const Velocity& velocity, const Color& color);

		// Moves the collision circle of the ball based on the ball's velocity
		void move(const float& delta, const int& screenWidth, const int& screenHeight, Ball** balls, const int& numBalls);

		// Renders the ball
		void render(SDL_Renderer* renderer);

		// Gets the ball's collision circle
		Circle getCollider() const;

		// Gets the velocity of the ball
		Velocity getVelocity() const;

		// Gets the color of the ball
		Color getColor() const;

	private:
		// The ball's collision circle
		Circle collider;

		// The velocity of the ball
		Velocity velocity;

		// The color of the ball
		Color color;
};


#endif
