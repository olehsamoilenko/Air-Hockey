#ifndef FIELD_HPP
# define FIELD_HPP

# include <SDL.h>
// # include <SDL_ttf.h>
# include "Paddle.hpp"
# include "Ball.hpp"

# define PADDLE_SIZE 100
# define WIN_HEIGHT 800
# define WIN_WIDTH 600
# define FPS 80

class Field
{
	public:
		Field();

		void LaunchGame();
	
	private:
		SDL_Window		*window;
		SDL_Surface		*surface;
		SDL_Surface		*grassSurface;
		SDL_Rect		grassRect;
	
		Ball			*ball;
		Paddle			*paddleMe;
		Paddle			*paddleOp;


		// void Init();
		void Show();
		void Close();
		void EventHandler();
	
};

#endif