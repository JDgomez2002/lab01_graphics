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

  std::vector<Vertex> polygon = {
    {321, 335},
    {521, 335},
    {521, 135},
    {321, 135},
  };

  framebuffer.createPolygon(polygon, white);
  framebuffer.fillPolygon(polygon, white);

  framebuffer.renderBuffer();
}

int main() {
  Framebuffer framebuffer(WIDTH, HEIGHT, clearColor);
  render(framebuffer);

  return 0;
}
