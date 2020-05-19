#include "game.h";

int main(int argc, char *argv[])
{

	Game.running = SDL_TRUE;

	Person Hero = {
		"resources/stick_figure.bmp",
		NULL,
		{0, 0, 32, 64},
		{0, 50, 32, 64},
		Direction::NONE,
		0,
	};
	game_start(&Hero);

	SDL_Event event;
	while (Game.running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				Game.running = SDL_FALSE;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				update(&Hero, event);
			}
		}
		render(&Hero);
		SDL_Delay(16);
	}

	game_end();

	return 0;
}