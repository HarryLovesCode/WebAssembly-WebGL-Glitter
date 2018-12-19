#include <iostream>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>

#include "camera.hpp"
#include "glitter.hpp"
#include "model.hpp"
#include "shader.hpp"

GLFWwindow *mWindow;
Camera cam;
Shader prog;
Model mod;

void draw()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    cam.update();
    prog.activate(cam);
    mod.draw(prog);
    prog.deactivate();

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_SAMPLES, 32);

    mWindow = glfwCreateWindow(mWidth, mHeight, "WebGL", NULL, NULL);

    if (mWindow == nullptr)
    {
        fprintf(stdout, "Failed to Create WebGL Context");
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(mWindow);

    fprintf(stdout, "WebGL %s\n", glGetString(GL_VERSION));

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    cam.init(mWindow);
    prog.init("shader.vert", "shader.frag");
    mod.load("scene.gltf");

    EmscriptenFullscreenStrategy strategy;
    strategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_DEFAULT;
    strategy.canvasResolutionScaleMode = EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF;
    strategy.filteringMode = EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;

    emscripten_request_fullscreen_strategy(NULL, 1, &strategy);
    emscripten_set_main_loop(draw, 0, 0);
}
