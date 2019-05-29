#include "Ball.hpp"
#include "Field.hpp"

Ball::Ball()
{
	ballRect.x = WIN_WIDTH / 2 - BALL_SIZE / 2 + 90;
	ballRect.y = WIN_HEIGHT / 2 - BALL_SIZE / 2  ;
	ballRect.w = BALL_SIZE;
	ballRect.h = BALL_SIZE;
	ballSurface = SDL_LoadBMP("resources/ball.bmp");
	speed_x = rand() % 14 - 7;
	speed_y = rand() % 14 - 7;
}

Ball::~Ball()
{
	SDL_FreeSurface(ballSurface);
}

static bool TochingWallVer(Ball *ball, Paddle *my, Paddle *op)
{
	if (ball->ballRect.y + ball->speed_y > WIN_HEIGHT - BALL_SIZE)
	{
		op->goal = true;
		return true;
	}
	if (ball->ballRect.y + ball->speed_y < 0)
	{
		my->goal = true;
		return true;
	}
	else
		return false;
}
static bool PaddleVerUp(Ball *ball, Paddle *paddle)
{
	if (ball->ballRect.y + ball->speed_y < paddle->paddleRect.y &&
		ball->ballRect.y + ball->speed_y + BALL_SIZE > paddle->paddleRect.y)
		return true;
	else
		return false;
}
static bool PaddleVerDown(Ball *ball, Paddle *paddle)
{
	if (ball->ballRect.y + ball->speed_y < paddle->paddleRect.y + PADDLE_SIZE &&
		ball->ballRect.y + ball->speed_y + BALL_SIZE > paddle->paddleRect.y + PADDLE_SIZE)
		return true;
	else
		return false;
}
static bool InPaddleWidth(Ball *ball, Paddle *paddle)
{
	if ((ball->ballRect.x >= paddle->paddleRect.x &&
		ball->ballRect.x <= paddle->paddleRect.x + PADDLE_SIZE) ||
		(ball->ballRect.x + BALL_SIZE >= paddle->paddleRect.x &&
		ball->ballRect.x + BALL_SIZE <= paddle->paddleRect.x + PADDLE_SIZE))
		return true;
	else
		return false;
}
static bool TochingPaddleVer(Ball *ball, Paddle *paddle)
{
	if (((PaddleVerUp(ball, paddle) && ball->speed_y > 0) ||   // mB without speed
		(PaddleVerDown(ball, paddle) && ball->speed_x < 0)) &&
		InPaddleWidth(ball, paddle))
	{
		if (ball->speed_x > 0)
			ball->speed_x += 1;
		else
			ball->speed_x -= 1;
		if (ball->speed_y > 0)
			ball->speed_y += 1;
		else
			ball->speed_y -= 1;
		return true;
	}
	else
		return false;
}

static bool TochingWallHor(Ball *ball)
{
	if (ball->ballRect.x + ball->speed_x > WIN_WIDTH - BALL_SIZE)
		return true;
	if  (ball->ballRect.x + ball->speed_x < 0)
		return true;
	return false;
}
static bool PaddleHorLeft(Ball *ball, Paddle *paddle)
{
	if (ball->ballRect.x + ball->speed_x < paddle->paddleRect.x &&
		ball->ballRect.x + ball->speed_x + BALL_SIZE > paddle->paddleRect.x)
		return true;
	else
		return false;
}
static bool PaddleHorRight(Ball *ball, Paddle *paddle)
{
	if (ball->ballRect.x + ball->speed_x < paddle->paddleRect.x + PADDLE_SIZE &&
		ball->ballRect.x + ball->speed_x + BALL_SIZE > paddle->paddleRect.x + PADDLE_SIZE)
		return true;
	else
		return false;
}
static bool InPaddleHeight(Ball *ball, Paddle *paddle)
{
	if ((ball->ballRect.y >= paddle->paddleRect.y &&
		ball->ballRect.y <= paddle->paddleRect.y + PADDLE_SIZE) ||
		(ball->ballRect.y + BALL_SIZE >= paddle->paddleRect.y &&
		ball->ballRect.y + BALL_SIZE <= paddle->paddleRect.y + PADDLE_SIZE))
		return true;
	else
		return false;
}
static bool TochingPaddleHor(Ball *ball, Paddle *paddle)
{
	if (((PaddleHorLeft(ball, paddle) && ball->speed_x > 0) ||   // mB without speed
		(PaddleHorRight(ball, paddle) && ball->speed_x < 0)) &&
		InPaddleHeight(ball, paddle))
	{
		if (ball->speed_x > 0)
			ball->speed_x += 1;
		else
			ball->speed_x -= 1;
		if (ball->speed_y > 0)
			ball->speed_y += 1;
		else
			ball->speed_y -= 1;
		return true;
	}
	else
		return false;
}

void	Ball::Move(Paddle *me, Paddle *op)
{

	if (TochingWallHor(this) ||
		TochingPaddleHor(this, me) ||
		TochingPaddleHor(this, op))
		speed_x *= -1;
	else
		ballRect.x += speed_x;

	if (TochingWallVer(this, me, op) ||
		TochingPaddleVer(this, me) ||
		TochingPaddleVer(this, op))
		speed_y *= -1;
	else
		ballRect.y += speed_y;
}

