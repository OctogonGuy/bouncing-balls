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

		// If the balls have collided, move back.
		if (distance < totalRadius)
		{
			float theta = -atan2(deltaY, deltaX);
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
	// Set color
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 1);

	// Draw circle according to Bresenham's circle drawing algorithm
	int cX = round(collider.x);
	int cY = round(collider.y);
	int r = collider.radius;
	int x = 0;
	int y = r;
	int dX = 2;
	int dY = -2 * r;
	int d = dX + dY + 1;
	while (x <= y)
	{
		SDL_RenderDrawLine(renderer, cX + x, cY - y, cX - x, cY - y);
		SDL_RenderDrawLine(renderer, cX + x, cY + y, cX - x, cY + y);
		SDL_RenderDrawLine(renderer, cX + y, cY - x, cX - y, cY - x);
		SDL_RenderDrawLine(renderer, cX + y, cY + x, cX - y, cY + x);
		if (d > 0)
		{
			y--;
			dY += 2;
			d += dY;
		}
		x++;
		dX += 2;
		d += dX + 1;
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
