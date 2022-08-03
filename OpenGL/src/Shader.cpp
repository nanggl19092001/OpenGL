#include "Shader.h"
#include "GL/glew.h"
#include "Renderer.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
{
	m_FilePath = filepath;

    ShaderProgramSource src = ParseShader(filepath);
    m_RendererId = CreateShader(src.vertexSource, src.fragmentSource);

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererId));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    int location = getUniformLocation(name);
    GLCall(glUniform4f(location, v1, v2, v3, v4));

}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_locationCache.find(name) != m_locationCache.end()) 
    {
        return m_locationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererId, name.c_str()));
    if(location == -1) 
        std::cout << "Warning: uniform " << name << " doesn't exist !" << std::endl;

    m_locationCache[name] = location;
    return location;
}



unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, NULL));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        if (result == GL_FALSE)
        {
            int length;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
            char* message = (char*)alloca(length * sizeof(char));
            GLCall(glGetShaderInfoLog(id, length, &length, message));

            LOG("Failed to compile");
            LOG((type == GL_VERTEX_SHADER ? " vertex " : " fragment "));

            LOG(message);

            GLCall(glDeleteShader(id));
            return 0;
        }

        return id;
    
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    
        std::ifstream stream(filepath);
        std::string line;

        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }

        return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}


