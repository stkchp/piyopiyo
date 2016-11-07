#pragma once

#include <cstdint>
#include <string>

#include <GLFW/glfw3.h>

#include "event.h"

namespace piyopiyo
{
class ppWindow
{
private:
  int width, height;
  double lastTime;
  std::uint64_t frames;
  std::uint8_t scale;
  std::string title;
  GLFWwindow* window;

public:
  int vwidth, vheight;
  int cx, cy;

  ppWindow();
  bool create();
  void destroy();
  void adjust();
  bool shouldClose();
  void clear();
  void swapBuffers();
  void pollEvents();
  void calcFps();
  void setTitle(const char* t) { title = t; };
  static ppEvents events;
  static void key_callback(GLFWwindow* w, int key, int scan, int act, int mods);
  static void mouse_callback(GLFWwindow* w, int button, int act, int mods);
  static void scroll_callback(GLFWwindow* w, double xoff, double yoff);
};
}
