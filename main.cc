#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main() {
    if (!glfwInit()) {
        std::cerr << "FAIL" << std::endl;
    } else {
        std::cout << "SUCCESS" << std::endl;
    }

    glfwTerminate();
}
