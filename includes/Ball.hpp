#ifndef BALL_HPP
# define BALL_HPP

# define BALL_SIZE 30

# include <SDL.h>

#include "Paddle.hpp"

class Ball
{
	public:
		Ball();
		~Ball();
	
		SDL_Surface		*ballSurface;
		SDL_Rect		ballRect;

		int speed_x;
		int speed_y;

		void	Move(Paddle *me, Paddle *op);
};

#endif