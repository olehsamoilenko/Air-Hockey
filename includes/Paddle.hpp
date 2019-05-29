#ifndef PADDLE_HPP
# define PADDLE_HPP

# include <SDL.h>

# define PADDLE_STEP 20

class Paddle
{
	public:
		Paddle(int x, int y, char *photo);
		~Paddle();
	
		SDL_Surface		*paddleSurface;
		SDL_Rect		paddleRect;
		bool			goal;
		int				goals;
		int				direction;

		void	MoveUp();
		void	MoveDown();
		void	MoveLeft();
		void	MoveRight();
		void	RandomMove();
		void	Defender();
	
};

#endif