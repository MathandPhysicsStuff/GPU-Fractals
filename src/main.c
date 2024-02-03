#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "glad/glad.h"

#include "header.h"

int main()
{
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window *window = NULL;
    SDL_GLContext gl_context = NULL;
    int info = FALSE; //setting info = TRUE will print opengl info to the terminal 

    GLuint vertex_array_object = 0;
    GLuint vertex_buffer_object = 0;
    GLuint index_buffer_object = 0;
    GLuint graphics_pipeline_object = 0;

    GLfloat vertices[] =
    {
        //top right 0
        0.5, 0.5, 0.0,
        
        //top left 1
        -0.5, 0.5, 0.0,
 
        //bottom left 2
        -0.5, -0.5, 0.0,     

        //bottom right 3
        0.5, -0.5, 0.0

        //triangle one -> 0 1 3
        //triangle two -> 1 2 3
    };
    int vertices_size = sizeof(vertices);

    /*
    const char* vertex_shader_source =
    "#version 460 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_position = vec4(position.x, position.y, position.z, position.w);\n"
    "}\n";

    const char* fragment_shader_source =
    "#version 460 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 0.5, 0.0, 1.0);\n"
    "}\n";
    */

    char *vertex_shader_source = read_file("./shaders/shader.glsl");
    char *fragment_shader_source = read_file("./shaders/fragment.glsl");

    if (vertex_shader_source == NULL)
        printf("Error reading vertex_shader_source\n");

    if (fragment_shader_source == NULL)
        printf("Error reading fragment_shader_source\n");

    //Initializes SDL and openGL 
    initialize(&window, &gl_context, SCREEN_WIDTH, SCREEN_HEIGHT, info); //function in src/initialize_free.c
    
    create_vertex_specs(vertices, vertices_size, 3, &vertex_array_object, &vertex_buffer_object, &index_buffer_object);
    create_graphics_pipeline(&graphics_pipeline_object, vertex_shader_source, fragment_shader_source);
 
    free(vertex_shader_source);
    free(fragment_shader_source);
   
    int running = TRUE;
    while (running == TRUE)
    {
        event_inputs(&running); //function in src/event_inputs.c
        
        predraw(&graphics_pipeline_object, SCREEN_WIDTH, SCREEN_HEIGHT);
        draw(&vertex_array_object, &vertex_buffer_object);

        SDL_GL_SwapWindow(window);
    }

    free_memory(&window, &graphics_pipeline_object, &vertex_array_object, &vertex_buffer_object); //function in src/initialize_free.c
    return 0;
}
