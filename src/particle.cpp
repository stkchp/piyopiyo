
#include <random>

#include <GL/gl.h>

#include "particle.h"

#define PP_PARTICLE_R (255)
#define PP_PARTICLE_G (50)
#define PP_PARTICLE_B (50)
#define PP_PARTICLE_SPAN (120)

namespace piyopiyo
{
particle::particle(std::int32_t _x, std::int32_t _y)
{
  std::random_device rd;
  x = _x;
  y = _y;
  frame = 0;
  vx = (rd() % 10) - 5.f;
  vy = rd() % 4 + 1;
  eol = false;
  span = (rd() % 120) + 60;
}

void particle::draw()
{
  float c = (span - frame) / (float)(span);
  glColor3f(c * PP_PARTICLE_R / 255.f, c * PP_PARTICLE_G / 255.f,
            c * PP_PARTICLE_B / 255.f);
  glBegin(GL_QUADS);
  glVertex2s(x, y);
  glVertex2s(x, y + 1);
  glVertex2s(x + 1, y + 1);
  glVertex2s(x + 1, y);
  glEnd();
  frame++;
  x += vx / 10.f;
  y += vy / 10.f;
  vx /= 1.5f;
  if (frame < span) return;
  eol = true;
}

void ppParticles::add(std::int32_t x, std::int32_t y)
{
  particles.push_back(particle(x, y));
}
void ppParticles::draw()
{
  for (auto &p : particles) {
    p.draw();
  }
}
void ppParticles::erase()
{
  auto itr = particles.begin();
  while (itr != particles.end()) {
    if (itr->eol) {
      itr = particles.erase(itr);
    } else {
      itr++;
    }
  }
}
}
