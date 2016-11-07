#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "window.h"

#define WIN_MAXWIDTH (128)
#define WIN_TITLE "TITLE"
#define WIN_SCALE (4)

namespace
{
// error callback
void error_callback(int error, const char* description)
{
  std::cerr << "ppWindow: error occured in GLFW : " << description << std::endl;
}
// key callback
}

namespace piyopiyo
{
ppEvents ppWindow::events = ppEvents();

void ppWindow::key_callback(GLFWwindow* w, int key, int scan, int act, int mods)
{
  if (act == GLFW_PRESS) {
    events.push(event(true, false, key));
  }
}
void ppWindow::mouse_callback(GLFWwindow* w, int button, int act, int mods)
{
  if (act == GLFW_PRESS) {
    events.push(event(false, true, button));
  }
}
void ppWindow::scroll_callback(GLFWwindow* w, double xoff, double yoff)
{
  events.push(event(xoff, yoff));
}

ppWindow::ppWindow()
{
  vwidth = WIN_MAXWIDTH;
  vheight = WIN_MAXWIDTH;
  width = 0;
  height = 0;
  lastTime = 0;
  frames = 0;
  scale = WIN_SCALE;
  title = WIN_TITLE;
}

bool ppWindow::create()
{
  // set error callback for glfw
  glfwSetErrorCallback(error_callback);

  // glfw init
  if (!glfwInit()) {
    return false;
  }

  // make window
  window = glfwCreateWindow(vwidth * scale, vheight * scale, title.c_str(),
                            NULL, NULL);

  if (!window) {
    glfwTerminate();
    return false;
  }

  // make this thread active
  glfwMakeContextCurrent(window);

  // keybord and mouse callback
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  // swap timing
  glfwSwapInterval(1);

  // calc ortho
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, vwidth, 0, vheight, -2.1f, 2.1f);

  // texture config
  glEnable(GL_TEXTURE_2D);
  glPixelStorei(GL_TEXTURE_2D, 4);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // model view mode...
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // clear color setting
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  return true;
}
void ppWindow::destroy()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void ppWindow::adjust()
{
  int _w, _h;

  std::cout << "X: " << cx << " Y: " << cy << std::endl;

  // set window size if window size changed.
  glfwGetFramebufferSize(window, &_w, &_h);

  if (_w == width && _h == height) return;

  // change window view size
  scale = 0;
  do {
    scale++;
    vwidth = _w / scale;
    vheight = _h / scale;
  } while (vwidth > WIN_MAXWIDTH || vheight > WIN_MAXWIDTH);

  // calc ortho
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, vwidth, 0, vheight, -2.1f, 2.1f);

  // model view mode...
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (scale * vwidth != _w || scale * vheight != _h)
    glfwSetWindowSize(window, scale * vwidth, scale * vheight);

  glfwGetFramebufferSize(window, &_w, &_h);

  int mw = scale * vwidth;
  int mh = scale * vheight;
  int left = (_w - mw) / 2;
  int top = (_h - mh) / 2;
  glViewport(left, top, mw, mh);

  std::cout << "ppWindow: Window size change detected!" << std::endl;
  std::cout << "ppWindow: old width = " << width << std::endl;
  std::cout << "ppWindow: old height = " << height << std::endl;
  std::cout << "ppWindow: new width = " << _w << std::endl;
  std::cout << "ppWindow: new height = " << _h << std::endl;
  std::cout << "ppWindow: ortho width = " << vwidth << std::endl;
  std::cout << "ppWindow: ortho height = " << vheight << std::endl;
  std::cout << "ppWindow: scale = " << (int)(scale) << std::endl;
  std::cout << "ppWindow: left = " << left << std::endl;
  std::cout << "ppWindow: top = " << top << std::endl;
  std::cout << "ppWindow: view width = " << mw << std::endl;
  std::cout << "ppWindow: view height = " << mh << std::endl;

  // save new window size.
  width = _w;
  height = _h;
}

void ppWindow::clear()
{
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  xpos = xpos - ((width - scale * vwidth) / 2);
  ypos = height - ypos - ((height - scale * vheight) / 2);
  cx = xpos / scale;
  cy = ypos / scale;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}
bool ppWindow::shouldClose()
{
  return glfwWindowShouldClose(window) != 0 ? true : false;
}

void ppWindow::swapBuffers() { glfwSwapBuffers(window); }
void ppWindow::pollEvents() { glfwPollEvents(); }
void ppWindow::calcFps()
{
  // Measure speed
  double currentTime = glfwGetTime();

  frames++;

  if (currentTime - lastTime >= 1.0) {
    std::stringstream str;

    str << title << " - [FPS: " << std::setprecision(2)
        << std::setiosflags(std::ios::fixed)
        << (frames / (currentTime - lastTime)) << "]";

    glfwSetWindowTitle(window, str.str().c_str());

    frames = 0;
    lastTime = currentTime;
  }
};
}
