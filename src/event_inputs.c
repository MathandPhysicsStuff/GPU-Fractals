#include "header.h"

void events(SDL_Event event, int *running)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *running = FALSE;
            break;
        }

        key_events(event, running);
        mouse_events(event);
    }
}

void key_events(SDL_Event event, int *running)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                *running = FALSE;
                break;
        }
    }
}

void mouse_events(SDL_Event event)
{

}










