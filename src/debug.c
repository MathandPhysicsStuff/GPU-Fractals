#include "header.h"

void GLClearAllErrors()
{
    while (glGetError() != GL_NO_ERROR)
    { }
}

int GLCheckErrorStatus(const char* function, int line)
{
    GLenum error;
    while (error = glGetError())
    {
        printf("OpenGL Error: %x\n Line: %d\n Function: %s\n", error, line, function);
        return TRUE;
    }
    return FALSE;
}


