#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "Framebuffer.cpp"
#include "Vertex.cpp"

const int HEIGHT = 500;
const int WIDTH = 800;
const Color clearColor = Color(0,0,0);

void render(Framebuffer &framebuffer) {
  const Color white = Color(255, 255, 255);
  const Color red = Color(255, 0, 0);
  const Color yellow = Color(255, 255, 0);
  const Color blue = Color(0, 0, 255);

  std::vector<Vertex> p1 = {
    {165, 380},
    {185, 360},
    {180, 330},
    {207, 345},
    {233, 330},
    {230, 360},
    {250, 380},
    {220, 385},
    {205, 410},
    {193, 383}
  };

  std::vector<Vertex> p2 = {
    {321, 335},
    {288, 286},
    {339, 251},
    {374, 302}
  };

  std::vector<Vertex> polygon3 = {
    {377, 249},
    {411, 197},
    {436, 249}
  };

  framebuffer.createPolygon(p1, white);
  framebuffer.fillPolygon(p1, yellow);

  framebuffer.createPolygon(p2, white);
  framebuffer.fillPolygon(p2, blue);

  framebuffer.createPolygon(polygon3, white);
  framebuffer.fillPolygon(polygon3, red);

  framebuffer.renderBuffer();
}

int main() {
  Framebuffer framebuffer(WIDTH, HEIGHT, clearColor);
  render(framebuffer);

  return 0;
}
