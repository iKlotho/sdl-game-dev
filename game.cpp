#include "game.h";
int frameIndex = 0;

void select_sprite(Person *person, int x, int y)
{
    person->spritePosition.x = x * person->spritePosition.w;
    person->spritePosition.y = y * person->spritePosition.h;
};

void draw_sprite(Person *person)
{
    //SDL_BlitSurface(Hero.sprite, &Hero.spritePosition, Game.screen.m_window_surface, dstrect);
    SDL_RenderCopy(Game.screen.renderer, person->texture, &person->spritePosition, &person->playerPosition);
}

void game_start(Person *person)
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
    SDL_Surface *sprite = SDL_LoadBMP(person->spriteFile);
    person->texture = SDL_CreateTextureFromSurface(Game.screen.renderer, sprite);
    SDL_FreeSurface(sprite);

    Game.running = SDL_TRUE;
}

void game_end()
{
    SDL_DestroyRenderer(Game.screen.renderer);
    SDL_DestroyWindow(Game.screen.window);

    Game.screen.window = NULL;
    Game.screen.renderer = NULL;

    SDL_Quit();
}
void update(Person *person, SDL_Event event)
{
    int x_width = 32;
    int y_height = 64;
    int rowUp = y_height * 0;
    int rowLeftRunning = y_height * 1;
    int rowRightRunning = y_height * 2;
    int rowDownRunning = y_height * 3;


    if (event.type == SDL_KEYDOWN)
    {
            if (person->currentSprite >= 8)
            {
                person->currentSprite = 1;
            }
            person->currentSprite += 1;
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            ++person->playerPosition.x;
            select_sprite(person, person->currentSprite, 2);
            break;
        case SDLK_LEFT:
            --person->playerPosition.x;
            select_sprite(person, person->currentSprite, 1);
            break;
        case SDLK_DOWN:
            ++person->playerPosition.y;
            select_sprite(person, person->currentSprite, 3);
            break;
        case SDLK_UP:
            --person->playerPosition.y;
            select_sprite(person, person->currentSprite, 0);
            break;
        default:
            select_sprite(person, 0, 0);
            break;
        }
    }
}

void render(Person *person)
{
    SDL_RenderClear(Game.screen.renderer);
    SDL_SetRenderDrawColor(Game.screen.renderer, 0, 255, 255, 255);
    draw_sprite(person);
    SDL_RenderPresent(Game.screen.renderer);
}