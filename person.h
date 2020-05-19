// Struct for random character

#include <SDL.h>

enum class Direction
{
	NONE,
	RIGHT,
	LEFT,
	UP,
};

typedef struct
{
    char *spriteFile;
	SDL_Texture *texture;
	SDL_Rect spritePosition;
	SDL_Rect playerPosition;
	Direction direction;
	int currentSprite;
} Person;
/*  = {
	NULL,
	NULL,
	{0, 0, 32, 64},
	{0, 50, 0, 0},
	Direction::NONE,
	0,
	select_sprite,
	draw_sprite,
	update,
};
*/

