
#include <iostream>

#include "Renderer.h"

void Renderer::GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool Renderer::GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        LOG("[OpenGL error]: ");
        LOG(error);
        LOG(function);
        LOG(file);
        LOG("Line: ");
        LOG(line);
        return false;
    }
    return true;
}
