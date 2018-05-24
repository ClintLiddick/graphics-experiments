#include <cstdlib>

#include <iostream>

#include "glad/glad.h"  // must be before all other GL includes

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_helper.hh"

constexpr GLuint WIDTH = 1280, HEIGHT = 1280;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (ImGui::GetIO().WantCaptureKeyboard) {
        imgui::KeyCallback(window, key, scancode, action, mode);
    } else {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "GL Test", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, imgui::MouseButtonCallback);
    glfwSetScrollCallback(window, imgui::ScrollCallback);
    glfwSetCharCallback(window, imgui::CharCallback);

    if (!gladLoadGL()) {
        std::cerr << "Failed to load OpenGL context" << std::endl;
        return EXIT_FAILURE;
    }

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto &imgui_io = ImGui::GetIO();
    imgui_io.Fonts->AddFontFromFileTTF("third-party/imgui/misc/fonts/Roboto-Medium.ttf", 15.0f);
    constexpr bool INSTALL_IMGUI_CALLBACKS = false;
    imgui::Init(window, INSTALL_IMGUI_CALLBACKS);
    ImGui::StyleColorsDark();

    // GL

    int success;
    char info_log[512];

    const char *vert_shader_txt = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

    uint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader, 1, &vert_shader_txt, nullptr);
    glCompileShader(vert_shader);
    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert_shader, 512, nullptr, info_log);
        std::cerr << "ERROR: " << info_log << std::endl;
        return EXIT_FAILURE;
    }

    const char *frag_shader_txt = R"(
#version 330 core
// in vec3 texCoord;
out vec4 frag_color;

void main()
{
    frag_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

    const uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader, 1, &frag_shader_txt, nullptr);
    glCompileShader(frag_shader);
    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag_shader, 512, nullptr, info_log);
        std::cerr << "ERROR: " << info_log << std::endl;
        return EXIT_FAILURE;
    }

    const uint shader_prog = glCreateProgram();
    glAttachShader(shader_prog, vert_shader);
    glAttachShader(shader_prog, frag_shader);
    glLinkProgram(shader_prog);

    glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_prog, 512, nullptr, info_log);
        std::cerr << "ERROR: " << info_log << std::endl;
        return EXIT_FAILURE;
    }

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    // TRIANGLE

    // clang-format off
    const float verts[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };

    const uint indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    // clang-format on

    uint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Run
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader_prog);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // imgui
        // TODO render on top
        // imgui::NewFrame();
        // ImGui::ShowDemoWindow();
        // ImGui::Render();
        // imgui::RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    imgui::Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
