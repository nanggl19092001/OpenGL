#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


static void glowChange(float& v1, float& increament, int& glowUp) {
    if (glowUp == 1)
    {
        if (v1 < 1.0f) {
            v1 += increament;
        }
        else {
            glowUp = 0;
        }
    }
    else {
        if (v1 > 0.0f) {
            v1 -= increament;
        }
        else {
            glowUp = 1;
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "openGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Something went wrong" << std::endl;
    }

    //1st triagle buffer
    {
        float verticesPositions[]{
            -0.5f,  -0.5f,
             0.5f,  -0.5f,
             0.5f,   0.5f,
            -0.5f,   0.5f

        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };


        //vertex array
        /*unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));*/

        VertexArray va;

        //vertexBuffer(data pointer, data array size)
        VertexBuffer vb(verticesPositions, 8);

        //layout
        /*GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));*/
        VertexBufferLayout layout;
        layout.PushFloat(2);
        va.AddBuffer(vb, layout);

        //index buffer(data pointer, data array size)
        IndexBuffer ib(indices, 6);

        Shader shader("res/shader/Basic.shader");

        float v1 = 0.0f, v2 = 0.25f, v3 = 0.3f, v4 = 0.0f;

        float increament = 0.01f;

        int glowUp = 1;

        shader.Bind();

        shader.setUniform4f("u_Color", v1, v2, v3, v4);

        va.Unbind();
        vb.Unbind();
        ib.UnbindIndexBuffer();
        shader.Unbind();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);


            glowChange(v1, increament, glowUp);

            shader.Bind();
            shader.setUniform4f("u_Color", v1, v2, v3, v4);

            va.Bind();
            ib.BindIndexBuffer();

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}