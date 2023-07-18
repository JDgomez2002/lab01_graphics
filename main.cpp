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

  std::vector<Vertex> polygon3 = {
    {377, 249},
    {411, 197},
    {436, 249}
  };

  framebuffer.createPolygon(polygon3, white);
  framebuffer.fillPolygon(polygon3, red);

  framebuffer.renderBuffer();
}

int main() {
  Framebuffer framebuffer(WIDTH, HEIGHT, clearColor);
  render(framebuffer);

  return 0;
}
