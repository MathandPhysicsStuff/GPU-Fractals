#include "header.h"

char* read_file(char *file_name)
{
    FILE *file;

    file = fopen(file_name, "r");
    
    if (file == NULL)
    {
        printf("%s could not be opened\n", file_name);
        return NULL;
    }

    fseek(file, 0, SEEK_END);

    int file_length = ftell(file);
    //printf("file length: %d\n", file_length);

    fseek(file, 0, SEEK_SET);
    
    char *string = malloc(sizeof(char) * (file_length+1));

    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}

GLuint compile_shader(GLuint type, const char* source)
{
    GLuint shader_object;

    if (type == GL_VERTEX_SHADER)
    {
        shader_object = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        shader_object = glCreateShader(GL_FRAGMENT_SHADER);
    }
    

    glShaderSource(shader_object, 1, &source, NULL);
    glCompileShader(shader_object);
    
    return shader_object;
}

GLuint create_shader_program(const char* vertex_shader_source, const char* fragment_shader_source)
{
    GLuint program_object = glCreateProgram();

    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);

    glAttachShader(program_object, vertex_shader);
    glAttachShader(program_object, fragment_shader);

    glLinkProgram(program_object);

    glValidateProgram(program_object);

    glDetachShader(program_object, vertex_shader);
    glDetachShader(program_object, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program_object;
}

void create_graphics_pipeline(GLuint *graphics_pipeline_object,
                              const char* vertex_shader_source, const char* fragment_shader_source)
{
    *graphics_pipeline_object = create_shader_program(vertex_shader_source, fragment_shader_source);
}

void create_vertex_specs(GLfloat *vertices, int vertices_size, GLint step_size,
                         GLuint *vertex_array_object, GLuint *vertex_buffer_object, GLuint *index_buffer_object)
{
    glGenVertexArrays(1, vertex_array_object);
    glBindVertexArray(*vertex_array_object);

    //Vertex Buffer Object
    glGenBuffers(1, vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices_size,
                 vertices,
                 GL_STATIC_DRAW);
    
    
    //index Buffer Object
    GLuint index_buffer_data[] = { 0,1,3, 1,2,3 }; 
    glGenBuffers(1, index_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *index_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(index_buffer_data),
                 index_buffer_data,
                 GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          step_size,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (void*)0);      

    glBindVertexArray(0);

    glDisableVertexAttribArray(0);           
}


















