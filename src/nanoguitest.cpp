#include <iostream>
#include <nanogui/screen.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/button.h>

int main()
{
  nanogui::init();

  nanogui::Screen screen({800, 600}, "Screen");
  nanogui::Window window(&screen, "Window");
  window.setPosition({15, 15});
  window.setLayout(new nanogui::GroupLayout());
  nanogui::Button *b = new nanogui::Button(&window, "My Button");
  b->setCallback([] { std::cout << "Button pressed!" << std::endl; });

  screen.performLayout();
  screen.drawAll();
  screen.setVisible(true);
  nanogui::mainloop();

  nanogui::shutdown();
  std::cout << "shut down" << std::endl;
  exit(EXIT_SUCCESS);
}
