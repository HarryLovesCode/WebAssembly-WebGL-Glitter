#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>
#include <vector>

Shader::Shader() {}

void Shader::init(std::string const &vs, std::string const &fs)
{
    program = glCreateProgram();

    load(vs);
    load(fs);
    link();
}

void Shader::load(std::string const &filename)
{
    GLint success = GL_FALSE;
    std::ifstream in(filename);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    GLuint shader = create(filename);

    const char *source = contents.c_str();

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, &errorLog[0]);

        std::cout << "Something went wrong" << std::endl;
        glDeleteShader(shader);

        return;
    }

    glAttachShader(program, shader);
}

void Shader::link()
{
    GLint success = GL_FALSE;

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, NULL, &errorLog[0]);

        std::cout << "Something went wrong" << std::endl;
        glDeleteProgram(program);

        return;
    }
}

void Shader::activate(Camera cam)
{
    glUseProgram(program);

    glm::mat4 persp = cam.getProj();
    glm::mat4 view = cam.getView();

    unsigned int transLoc = glGetUniformLocation(program, "model");
    unsigned int perspLoc = glGetUniformLocation(program, "projection");

    glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(perspLoc, 1, GL_FALSE, glm::value_ptr(persp));
}

void Shader::deactivate()
{
    glUseProgram(NULL);
}

GLuint Shader::create(std::string const &filename)
{
    auto index = filename.rfind(".");
    auto ext = filename.substr(index + 1);

    if (ext == "vert")
    {
        return glCreateShader(GL_VERTEX_SHADER);
    }
    else if (ext == "frag")
    {
        return glCreateShader(GL_FRAGMENT_SHADER);
    }
    else
    {
        return false;
    }
}