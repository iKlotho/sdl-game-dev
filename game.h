// initialize the game
#include "defs.h";

struct
{
	SDL_bool running;
	struct
	{
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Surface *m_window_surface;
	} screen;
	struct
	{
		unsigned int n;
		SDL_Surface **spritesheet;
	} gfx;
} Game = {
	SDL_FALSE,
	{NULL,
	 NULL,
	 NULL},
	{0,
	 NULL},
};

void game_start(Person *person);
void game_end();
void render(Person *person);
void update(Person *person, SDL_Event event);
void select_sprite(Person *person, int x, int y);
void draw_sprite(Person *person);