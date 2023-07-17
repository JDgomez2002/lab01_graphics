#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include "Color.cpp"
#include "Vertex.cpp"

class Framebuffer {
public:
  Framebuffer(int width, int height, const Color &clearColor);
  Color &getPixel(int x, int y);
  void point(const Vertex &vertex, const Color &currentColor);
  void clear(const Color &clearColor);
  void renderBuffer();
  void line(const Vertex &p0, const Vertex &p1, const Color &currentColor);
  void createPolygon(const std::vector<Vertex> &vertices, const Color &currentColor);
  void fillPolygon(const std::vector<Vertex> &vertices, const Color &currentColor);

private:
  int width;
  int height;
  std::vector<Color> pixels;
  bool isValidCoordinate(int x, int y);
  bool isInsidePolygon(int x, int y, const std::vector<Vertex> &vertices);
  void writeBmpHeader(std::ofstream &file);
};

Framebuffer::Framebuffer(int width, int height, const Color &clearColor) : width(width), height(height), pixels(width * height, clearColor){}

Color &Framebuffer::getPixel(int x, int y) {
  return pixels[y * width + x];
}

void Framebuffer::point(const Vertex &vertex, const Color &currentColor) {
  if (isValidCoordinate(vertex.x, vertex.y)) {
    int index = vertex.y * width + vertex.x;
    pixels[index] = currentColor;
  }
}

void Framebuffer::clear(const Color &clearColor) {
  std::fill(pixels.begin(), pixels.end(), clearColor);
}

void Framebuffer::renderBuffer() {
  std::ofstream file("out.bmp", std::ios::binary);

  // Write BMP header
  writeBmpHeader(file);

  // Write pixel data
  for (const auto &color : pixels) {
    // Write color components in BGR order
    file.put(color.getBlue());
    file.put(color.getGreen());
    file.put(color.getRed());
  }

  file.close();
}

void Framebuffer::line(const Vertex &p0, const Vertex &p1, const Color &currentColor) {
  int x0 = p0.x;
  int y0 = p0.y;
  int x1 = p1.x;
  int y1 = p1.y;

  int dx = std::abs(x1 - x0);
  int dy = std::abs(y1 - y0);

  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (x0 != x1 || y0 != y1) {
    Vertex current{x0, y0};
    point(current, currentColor);

    int err2 = 2 * err;
    if (err2 > -dy)
    {
      err -= dy;
      x0 += sx;
    }
    if (err2 < dx)
    {
      err += dx;
      y0 += sy;
    }
  }
}

void Framebuffer::createPolygon(const std::vector<Vertex> &vertices, const Color &currentColor) {
  for (int i = 0; i < vertices.size() - 1; i++) {
    line(vertices[i], vertices[i + 1], currentColor);
  }
  line(vertices[vertices.size() - 1], vertices[0], currentColor);
}

void Framebuffer::fillPolygon(const std::vector<Vertex> &vertices, const Color &fillColor) {
  // Find the bounding box of the polygon
  int minX = width;
  int maxX = 0;
  int minY = height;
  int maxY = 0;

  for (const auto &vertex : vertices) {
    minX = std::min(minX, vertex.x);
    maxX = std::max(maxX, vertex.x);
    minY = std::min(minY, vertex.y);
    maxY = std::max(maxY, vertex.y);
  }

  // Iterate over each pixel within the bounding box
  for (int y = minY; y <= maxY; ++y) {
    for (int x = minX; x <= maxX; ++x) {
      // Check if the current pixel is inside the polygon
      if (isInsidePolygon(x, y, vertices)) {
        point({x, y}, fillColor);
      }
    }
  }
}

bool Framebuffer::isInsidePolygon(int x, int y, const std::vector<Vertex> &vertices) {
  int numVertices = vertices.size();
  bool inside = false;

  for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
    if (((vertices[i].y > y) != (vertices[j].y > y)) && (x < (vertices[j].x - vertices[i].x) * (y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x)) {
      inside = !inside;
    }
  }

  return inside;
}

bool Framebuffer::isValidCoordinate(int x, int y) {
  return x >= 0 && x < width && y >= 0 && y < height;
}

void Framebuffer::writeBmpHeader(std::ofstream &file) {
  // BMP header structure
  #pragma pack(push, 1) // Ensure struct is tightly packed
  struct BitmapHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitDepth;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t totalColors;
    uint32_t importantColors;
  };
#pragma pack(pop) // Restore previous packing setting

  BitmapHeader header;
  std::memset(&header, 0, sizeof(BitmapHeader));

  header.type = 0x4D42; // BM
  header.size = sizeof(BitmapHeader) + pixels.size() * 3; // 3 bytes per pixel
  header.offset = sizeof(BitmapHeader);
  header.headerSize = sizeof(BitmapHeader) - 14; // subtracting the size of the common fields
  header.width = width;
  header.height = height;
  header.planes = 1;
  header.bitDepth = 24;
  header.compression = 0;
  header.imageSize = width * height * 3; // 3 bytes per pixel
  header.xPixelsPerMeter = 2835; // 72 dpi
  header.yPixelsPerMeter = 2835; // 72 dpi
  header.totalColors = 0;
  header.importantColors = 0;

  file.write(reinterpret_cast<const char *>(&header), sizeof(BitmapHeader));
}
