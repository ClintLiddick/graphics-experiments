#pragma once

struct GLFWwindow;

namespace imgui {

bool Init(GLFWwindow *window, bool install_callbacks, const char *glsl_version = nullptr);
void Shutdown();
void NewFrame();
void RenderDrawData(ImDrawData *draw_data);

// Use if you want to reset your rendering device without losing ImGui state.
void InvalidateDeviceObjects();
bool CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void CharCallback(GLFWwindow *window, unsigned int c);

}  // namespace imgui
