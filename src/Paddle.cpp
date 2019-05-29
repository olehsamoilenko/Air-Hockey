#include "Paddle.hpp"
#include "Field.hpp"

Paddle::Paddle(int x, int y, char* photo)
{
	paddleRect.x = x;
	paddleRect.y = y;
	paddleRect.w = PADDLE_SIZE;
	paddleRect.h = PADDLE_SIZE;
	paddleSurface = SDL_LoadBMP(photo);
	goal = false;
	goals = 0;
	direction = 0;
}

Paddle::~Paddle()
{
	SDL_FreeSurface(paddleSurface);
}

void	Paddle::MoveLeft()
{
	paddleRect.x -= PADDLE_STEP;
	if (paddleRect.x < 0)
		paddleRect.x = 0;
}

void	Paddle::MoveRight()
{
	paddleRect.x += PADDLE_STEP;
	if (paddleRect.x > WIN_WIDTH - PADDLE_SIZE)
		paddleRect.x = WIN_WIDTH - PADDLE_SIZE;
}

void	Paddle::MoveUp()
{
	paddleRect.y -= PADDLE_STEP;
	if (paddleRect.y < 0)
		paddleRect.y = 0;
}

void	Paddle::MoveDown()
{
	paddleRect.y += PADDLE_STEP;
	if (paddleRect.y > WIN_HEIGHT - PADDLE_SIZE)
		paddleRect.y = WIN_HEIGHT - PADDLE_SIZE;
}

void	Paddle::RandomMove()
{
	int move = rand() % 4;
	switch (move)
	{
		case 0:
			MoveLeft();
			break;
		
		case 1:
			MoveRight();
			break;

		case 2:
			MoveUp();
			break;

		case 3:
			MoveDown();
			break;
	
		default:
			break;
	}
}

void	Paddle::Defender()
{
	if (direction < 20)
		MoveRight();
	else
		MoveLeft();
	direction++;
	if (direction == 40)
		direction = 0;
}
