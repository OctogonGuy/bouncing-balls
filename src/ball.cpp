#include "ball.h"

#define _USE_MATH_DEFINES
#include <math.h>


Ball::Ball(const Circle& collider, const Velocity& velocity, const Color& color)
{
	this->collider = collider;
	this->velocity = velocity;
	this->color = color;
}


void Ball::move(const float& delta, const int& screenWidth, const int& screenHeight, Ball** balls, const int& numBalls)
{
	// Advance position
	collider.x += velocity.speed * delta/1000 * cos(velocity.angle);
	collider.y -= velocity.speed * delta/1000 * sin(velocity.angle);

	// Check for collision with edge of screen. If so, move back.
	// Top
	if (collider.y - collider.radius < 0)
	{
		collider.y -= (collider.y - collider.radius);
		velocity.angle = -velocity.angle;
	}
	// Right
	if (collider.x + collider.radius > screenWidth)
	{
		collider.x -= (collider.x + collider.radius) - screenWidth;
		velocity.angle = M_PI - velocity.angle;
	}
	// Bottom
	if (collider.y + collider.radius > screenHeight)
	{
		collider.y -= (collider.y + collider.radius) - screenHeight;
		velocity.angle = -velocity.angle;
	}
	// Left
	if (collider.x - collider.radius < 0)
	{
		collider.x -= (collider.x - collider.radius);
		velocity.angle = M_PI - velocity.angle;
	}

	// Check for collision with other balls
	for (int i = 0; i < numBalls; i++)
	{
		// Skip itself
		if (balls[i] == this)
		{
			continue;
		}

		// Calculate necessary quantities
		float deltaX = this->collider.x - balls[i]->collider.x;
		float deltaY = this->collider.y - balls[i]->collider.y;
		float totalRadius = this->collider.radius + balls[i]->collider.radius;
		float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
		float theta = -atan2(deltaY, deltaX);

		// If the balls have collided, move back.
		if (distance < totalRadius)
		{
			float timeSinceCollision = (distance / totalRadius) * delta;
			this->velocity.angle = theta;
			this->collider.x += this->velocity.speed * timeSinceCollision/1000 * cos(this->velocity.angle);
			this->collider.y -= this->velocity.speed * timeSinceCollision/1000 * sin(this->velocity.angle);
			balls[i]->velocity.angle = theta - M_PI;
			balls[i]->collider.x += balls[i]->velocity.speed * timeSinceCollision/1000 * cos(balls[i]->velocity.angle);
			balls[i]->collider.y -= balls[i]->velocity.speed * timeSinceCollision/1000 * sin(balls[i]->velocity.angle);
		}
	}
}


void Ball::render(SDL_Renderer* renderer)
{
	// Get bounds of circle
	int cX = round(collider.x);
	int sX = round(collider.x - collider.radius);
	int eX = round(collider.x + collider.radius);
	int cY = round(collider.y);
	int sY = round(collider.y - collider.radius);
	int eY = round(collider.y + collider.radius);
	int r = collider.radius;

	// Set color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);

	// Render the appropriate pixels of the circle
	for (int x = sX; x < eX; x++)
	{
		for (int y = sY; y < eY; y++)
		{
			if (pow(x - cX, 2) + pow(y - cY, 2) <= pow(r, 2))
			{
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
	}
}


Circle Ball::getCollider() const
{
	return collider;
}


Velocity Ball::getVelocity() const
{
	return velocity;
}


Color Ball::getColor() const
{
	return color;
}
