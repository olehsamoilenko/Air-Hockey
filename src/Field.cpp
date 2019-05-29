#include "Field.hpp"
#include <cstdio>

Field::Field()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	window = SDL_CreateWindow("Air-Hockey by osamoile",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WIN_WIDTH, WIN_HEIGHT,
		SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	grassSurface = SDL_LoadBMP("resources/grass.bmp");
	char me[] = "resources/me.bmp";
	paddleMe = new Paddle(
		WIN_WIDTH / 2 - PADDLE_SIZE / 2,
		WIN_HEIGHT - 2 * PADDLE_SIZE,
		me);
	char op[] = "resources/op.bmp";
	paddleOp = new Paddle(
		WIN_WIDTH / 2 - PADDLE_SIZE / 2,
		PADDLE_SIZE,
		op);
	ball = new Ball();
	grassRect.x = 0;
	grassRect.y = 0;
	grassRect.h = WIN_HEIGHT;
	grassRect.w = WIN_WIDTH;
}

void	Field::Show()
{
	SDL_BlitScaled(grassSurface, NULL, surface, &grassRect);
	SDL_BlitScaled(paddleMe->paddleSurface, NULL, surface, &paddleMe->paddleRect);
	SDL_BlitScaled(paddleOp->paddleSurface, NULL, surface, &paddleOp->paddleRect);
	SDL_BlitScaled(ball->ballSurface, NULL, surface, &ball->ballRect);
	SDL_UpdateWindowSurface(window);
}

void	Field::Close()
{
	SDL_FreeSurface(grassSurface);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	Field::EventHandler()
{
	bool quit = false;
	SDL_Event e;

	while (!quit)
	{
		SDL_Delay(1000 / FPS);
		ball->Move(paddleMe, paddleOp);
		if (paddleMe->goals >= 3)
			paddleOp->Defender();
		else if (paddleMe->goals >= 1)
			paddleOp->RandomMove();
		if (paddleMe->goal || paddleOp->goal)
		{
			float len = WIN_WIDTH / 2 - ball->ballRect.x;
			if (len < 0)
				len *= -1;
			if (len <= WIN_WIDTH / 10)
			{
				ball = new Ball();
				if (paddleMe->goal)
				{
					paddleMe->goals += 1;
					printf("Goal performed by ME! %d:%d\n", paddleMe->goals, paddleOp->goals);
				}
				else
				{
					paddleOp->goals += 1;
					printf("Goal performed by OP! %d:%d\n", paddleMe->goals, paddleOp->goals);
				}
			}
			paddleMe->goal = false;
			paddleOp->goal = false;
			if (paddleMe->goals == 5)
			{
				printf("YOU WON!\n");
				quit = true;
			}
			if (paddleOp->goals == 5)
			{
				printf("YOU LOSE!\n");
				quit = true;
			}
			
		}
		Show();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_LEFT:
						paddleMe->MoveLeft();
						break;

					case SDLK_RIGHT:
						paddleMe->MoveRight();
						break;

					case SDLK_UP:
						paddleMe->MoveUp();
						break;

					case SDLK_DOWN:
						paddleMe->MoveDown();
						break;

					case SDLK_ESCAPE:
						quit = true;
					
					default:
						break;
				}
			}
		}
	}
}

void	Field::LaunchGame()
{
	EventHandler();
	Close();
}
