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
  const Color yellow = Color(255, 255, 0);
  const Color blue = Color(0, 0, 255);

  std::vector<Vertex> p2 = {
    {321, 335},
    {288, 286},
    {339, 251},
    {374, 302}
  };

  framebuffer.createPolygon(p2, white);
  framebuffer.fillPolygon(p2, blue);

  framebuffer.renderBuffer();
}

int main() {
  Framebuffer framebuffer(WIDTH, HEIGHT, clearColor);
  render(framebuffer);

  return 0;
}
