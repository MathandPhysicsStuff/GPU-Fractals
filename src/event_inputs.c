#include "header.h"

void event_inputs(int *running, UniformVariables *U)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            *running = FALSE;
            break;
        }

        key_events(event, running, U);
        mouse_events(event, U);
    }
}

void key_events(SDL_Event event, int *running, UniformVariables *U)
{
    float zoom_in = 0.9;
    float zoom_out = 1.5;
    int zoom_level = 0;

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {

            case SDLK_ESCAPE:
                *running = FALSE;
                break;

            case SDLK_UP:
                U->y_point += U->step;
                break;

            case SDLK_DOWN:
                U->y_point -= U->step;
                break;

            case SDLK_LEFT:
                U->x_point -= U->step;
                break;

            case SDLK_RIGHT:
                U->x_point += U->step;
                break;

            case SDLK_z:
                U->lx_off *= zoom_in;            
                U->ux_off *= zoom_in;            
                U->ly_off *= zoom_in;            
                U->uy_off *= zoom_in;     
                U->step *= zoom_in;            
                U->zoom_level += 1;         
                break;

            case SDLK_x:
                U->lx_off *= zoom_out;            
                U->ux_off *= zoom_out;            
                U->ly_off *= zoom_out;            
                U->uy_off *= zoom_out;     
                U->step *= zoom_out;   
                U->zoom_level -= 1;         
                break;

            case SDLK_i:
                U->iter += 64;
                break;
 
            case SDLK_o:
                if (U->iter > 64)
                    U->iter -= 64;
                break;
               
            case SDLK_p:
                printf("info:\n");
                printf("position: %f, %f\n", U->x_point, U->y_point);
                printf("iterations: %d\n", U->iter);
                printf("zoom level: %d\n\n", U->zoom_level);
                break;

        }
    }
}

void mouse_events(SDL_Event event, UniformVariables *U)
{

}










