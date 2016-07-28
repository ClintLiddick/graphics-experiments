#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

constexpr GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GL Test", NULL, NULL);
  glfwMakeContextCurrent(window);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    return -1;
  }

  glfwSetKeyCallback(window, key_callback);

  if (gl3wInit()) {
    std::cerr << "Failed to load OpenGL context" << std::endl;
    return -1;
  }

  if (!gl3wIsSupported(3, 1)) {
    std::cerr << "OpenGL 3.1 not supported" << std::endl;
  }

  glViewport(0, 0, WIDTH, HEIGHT);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}
