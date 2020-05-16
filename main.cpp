

#include <SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SCALE 1
#define SCREEN_NAME "DevApp"

void game_start();
void game_end();

struct {
    SDL_bool running;
    struct {
		SDL_Window* window;
		SDL_Renderer* renderer;
	} screen;
    void (*init)(void);
    void (*quit)(void);
} Game = {
    SDL_FALSE,
    {
		NULL,
		NULL
	},
    game_start,
    game_end
};

void game_start(void) {
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0) {
		printf("SDL error -> %sn", SDL_GetError());
		exit(1);
	}

	Game.screen.window = SDL_CreateWindow(
		SCREEN_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
	);
	Game.screen.renderer = SDL_CreateRenderer(
		Game.screen.window, -1,
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);

	Game.running = SDL_TRUE;
}

void game_end(void) {
    SDL_DestroyRenderer(Game.screen.renderer);
	SDL_DestroyWindow(Game.screen.window);

	Game.screen.window = NULL;
	Game.screen.renderer = NULL;

	SDL_Quit();
}

int main(int argc, char* argv[]) {

	Game.init();

	SDL_Event event;
	while(Game.running) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT: {
					Game.running = SDL_FALSE;
				} break;
			}
		}

		SDL_RenderClear(Game.screen.renderer);
		SDL_RenderPresent(Game.screen.renderer);
	}

	Game.quit();

	return 0;
}