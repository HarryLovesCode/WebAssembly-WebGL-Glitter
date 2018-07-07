#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

enum CameraDirection
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
  private:
    void keyboardPress();
    void mouseMove();
    void keyboardPress(CameraDirection direction);

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 globalUp;
    float yaw, pitch;
    float speed;
    float sensitivity;
    GLFWwindow *window;

  public:
    Camera();

    void init(GLFWwindow *window);
    void update();
    glm::mat4 getView();
    glm::mat4 getProj();
};

#endif