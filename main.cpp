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
  const Color green = Color(0, 255, 0);
  const Color black = Color(0, 0, 0);

  std::vector<Vertex> polygon = {
    {321, 335},
    {521, 335},
    {521, 135},
    {321, 135},
  };

  std::vector<Vertex> polygon4 = {
    {413, 177},
    {448, 159},
    {502, 88},
    {553, 53},
    {535, 36},
    {676, 37},
    {660, 52},
    {750, 145},
    {761, 179},
    {672, 192},
    {659, 214},
    {615, 214},
    {632, 230},
    {580, 230},
    {597, 215},
    {552, 214},
    {517, 144},
    {466, 180}
  };

  std::vector<Vertex> polygon5 = {
    {682, 175},
    {708, 120},
    {735, 148},
    {739, 170}
  };

  framebuffer.createPolygon(polygon4, white);
  framebuffer.fillPolygon(polygon4, green);
  
  framebuffer.createPolygon(polygon5, white);
  framebuffer.fillPolygon(polygon5, black);

  framebuffer.renderBuffer();
}

int main() {
  Framebuffer framebuffer(WIDTH, HEIGHT, clearColor);
  render(framebuffer);

  return 0;
}
