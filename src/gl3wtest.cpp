#include <iostream>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

constexpr GLuint WIDTH = 800, HEIGHT = 600;

// clang-format off
static const GLfloat points[] = {
   0.0f,  0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
  -0.5f, -0.5f,  0.0f
};
// clang-format on

static const char* v_shader =
    "#version 330\n"
    "layout (location = 0) in vec3 vp;"
    "void main() {"
    "gl_Position = vec4 (vp, 1.0);"
    "}";

static const char* f_shader =
    "#version 330\n"
    "out vec4 color;"
    "void main() {"
    "color = vec4 (0.5, 0.0, 0.5, 1.0);"
    "}";

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

  // setup shaders
  GLint success;
  GLchar compile_log[512];

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &v_shader, NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, 512, NULL, compile_log);
    std::cerr << "ERROR VS: " << compile_log << std::endl;
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &f_shader, NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vs, 512, NULL, compile_log);
    std::cerr << "ERROR FS: " << compile_log << std::endl;
  }

  GLint shader_prog = glCreateProgram();
  glAttachShader(shader_prog, vs);
  glAttachShader(shader_prog, fs);
  glLinkProgram(shader_prog);
  glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(vs, 512, NULL, compile_log);
    std::cerr << "ERROR PROG: " << compile_log << std::endl;
  }
  glDeleteShader(vs);
  glDeleteShader(fs);

  // setup vertex objects
  GLuint vao = 0;
  GLuint vbo = 0;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);  // unbind vao

  GLenum err;
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_prog);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error using shader: " << err << std::endl;
      break;
    }
    glBindVertexArray(vao);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error binding array: " << err << std::endl;
      break;
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error drawing: " << err << std::endl;
      break;
    }
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
  glfwTerminate();
  return 0;
}
