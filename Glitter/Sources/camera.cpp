#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;
    sensitivity = 0.1f;
    speed = 0.5f;
}

void Camera::init(GLFWwindow *window)
{
    this->window = window;
}

void Camera::update()
{
    mouseMove();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        keyboardPress(FORWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        keyboardPress(BACKWARD);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        keyboardPress(LEFT);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        keyboardPress(RIGHT);
    }

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, globalUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::mouseMove()
{
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    yaw = x * sensitivity;
    pitch = -y * sensitivity;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }
}

void Camera::keyboardPress(CameraDirection direction)
{
    if (direction == FORWARD)
    {
        position += front * speed;
    }
    else if (direction == BACKWARD)
    {
        position -= front * speed;
    }
    else if (direction == LEFT)
    {
        position -= right * speed;
    }
    else if (direction == RIGHT)
    {
        position += right * speed;
    }
}

glm::mat4 Camera::getView()
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProj()
{
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    return glm::perspective(1.0, (double)width / (double)height, 0.1, 100.0);
}