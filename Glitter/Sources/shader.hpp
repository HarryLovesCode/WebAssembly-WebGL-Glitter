#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>

#include "camera.hpp"

class Shader
{
  private:
    GLuint create(std::string const &filename);
    void load(std::string const &filename);
    void link();

  public:
    Shader();

    void activate(Camera cam);
    void init(std::string const &vs, std::string const &fs);
    void deactivate();

    GLuint program;
};

#endif