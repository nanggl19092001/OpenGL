#pragma once

#include<GL/glew.h>
#include<iostream>

#define LOG(x) std::cout << x << std::endl;
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) Renderer::GLClearError();\
    x;\
    ASSERT(Renderer::GLLogCall(#x, __FILE__, __LINE__))

class Renderer
{
public:
    static void GLClearError();

    static bool GLLogCall(const char* function, const char* file, int line);
};

