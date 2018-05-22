#include <cstdlib>

#include <iostream>

#include "glad/glad.h"  // must be before all other GL includes

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_helper.hh"

constexpr GLuint WIDTH = 1280, HEIGHT = 720;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    std::cout << "CLINT: keypress" << std::endl;
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
    imgui_io.Fonts->AddFontFromFileTTF("third-party/imgui/misc/fonts/Roboto-Medium.ttf",
                                       15.0f,
                                       nullptr,
                                       imgui_io.Fonts->GetGlyphRangesChinese());
    imgui_io.Fonts->AddFontFromFileTTF("third-party/imgui/misc/fonts/Roboto-Medium.ttf",
                                       15.0f,
                                       nullptr,
                                       imgui_io.Fonts->GetGlyphRangesJapanese());
    constexpr bool INSTALL_IMGUI_CALLBACKS = false;
    imgui::Init(window, INSTALL_IMGUI_CALLBACKS);
    ImGui::StyleColorsDark();

    // Run
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        imgui::NewFrame();
        // ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
        ImGui::ShowDemoWindow();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();
        imgui::RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    imgui::Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
