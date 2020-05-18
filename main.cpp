

#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "DevApp"

void game_start();
void game_end();
void select_sprite(int x, int y);
void draw_sprite();
void update(SDL_KeyCode sym);

struct
{
	SDL_bool running;
	SDL_Rect playerPos;
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
	void (*init)(void);
	void (*quit)(void);
} Game = {
	SDL_FALSE,
	{32, 0, 32, 64},
	{NULL,
	 NULL,
	 NULL},
	{0,
	 NULL},
	game_start,
	game_end};

enum class Direction
{
	NONE,
	RIGHT,
	LEFT,
	UP,
};

struct
{
	SDL_Surface *sprite;
	SDL_Texture *texture;
	SDL_Rect position;
	Direction direction;
	int m_spritesheet_column;
	void (*select_sprite)(int x, int y);
	void (*draw_sprite)(void);
	void (*update)(SDL_KeyCode sym);
} Hero = {
	NULL,
	NULL,
	{0, 0, 32, 64},
	Direction::NONE,
	0,
	select_sprite,
	draw_sprite,
	update,

};

void update(SDL_KeyCode sym)
{
	int x_width = 32;
	int y_height = 64;
	int rowUp = y_height * 0;
	int rowLeftRunning = y_height * 1;
	int rowRightRunning = y_height * 2;
	int rowDownRunning = y_height * 3;

	printf("m spritesheet col %d\n", Hero.m_spritesheet_column);
	if (Hero.m_spritesheet_column >= 8)
	{
		Hero.m_spritesheet_column = 1;
	}
	Hero.m_spritesheet_column += 1;
	switch (sym)
	{
	case SDLK_RIGHT:
		Hero.select_sprite(Hero.m_spritesheet_column, 2);
		break;
	case SDLK_LEFT:
		Hero.select_sprite(Hero.m_spritesheet_column, 1);
		break;
	case SDLK_DOWN:
		Hero.select_sprite(Hero.m_spritesheet_column, 3);
		break;
	case SDLK_UP:
		Hero.select_sprite(Hero.m_spritesheet_column, 0);
		break;
	default:
		Hero.select_sprite(0, 0);
		break;
	}
}

void select_sprite(int x, int y)
{
	Hero.position.x = x * Hero.position.w;
	Hero.position.y = y * Hero.position.h;
};

void draw_sprite(void)
{
	//SDL_BlitSurface(Hero.sprite, &Hero.position, Game.screen.m_window_surface, dstrect);
	SDL_RenderCopy(Game.screen.renderer, Hero.texture, &Hero.position, &Game.playerPos);
}

void game_start(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL error -> %sn", SDL_GetError());
		exit(1);
	}

	Game.screen.window = SDL_CreateWindow(
		SCREEN_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		0);

	Game.screen.renderer = SDL_CreateRenderer(
		Game.screen.window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Game.screen.m_window_surface = SDL_GetWindowSurface(Game.screen.window);

	Hero.sprite = SDL_LoadBMP("resources/stick_figure.bmp");
	Hero.texture = SDL_CreateTextureFromSurface(Game.screen.renderer, Hero.sprite);

	Game.running = SDL_TRUE;
}

void game_end(void)
{
	SDL_DestroyRenderer(Game.screen.renderer);
	SDL_DestroyWindow(Game.screen.window);

	Game.screen.window = NULL;
	Game.screen.renderer = NULL;

	SDL_Quit();
}

void render()
{
	SDL_RenderClear(Game.screen.renderer);
	SDL_SetRenderDrawColor(Game.screen.renderer, 0, 255, 255, 255);
	Hero.draw_sprite();
	SDL_RenderPresent(Game.screen.renderer);
}

int main(int argc, char *argv[])
{

	Game.init();

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
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
					++Game.playerPos.x;
					Hero.update(SDLK_RIGHT);
					break;
				case SDLK_LEFT:
					--Game.playerPos.x;
					Hero.update(SDLK_LEFT);
					break;
					// Remeber 0,0 in SDL is left-top. So when the user pressus down, the y need to increase
				case SDLK_DOWN:
					Hero.update(SDLK_DOWN);
					++Game.playerPos.y;
					break;
				case SDLK_UP:
					Hero.update(SDLK_UP);
					--Game.playerPos.y;
					break;
				default:
					break;
				}
			}
		}
		render();
	}

	Game.quit();

	return 0;
}