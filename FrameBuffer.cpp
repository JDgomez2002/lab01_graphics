#include <iostream>
#include <fstream>
#include <vector>

class Framebuffer {
private:
    static const int WIDTH = 800;  // Width of the framebuffer
    static const int HEIGHT = 600; // Height of the framebuffer
    static const int BYTES_PER_PIXEL = 3; // Number of bytes per pixel (assuming RGB)

    std::vector<uint8_t> framebuffer; // The framebuffer vector

public:
    Framebuffer() : framebuffer(WIDTH * HEIGHT * BYTES_PER_PIXEL, 0) {}

    void clear() {
        // Fill the framebuffer with black color (RGB: 0, 0, 0)
        std::fill(framebuffer.begin(), framebuffer.end(), 0);
    }

    void renderBuffer() {
        // Create a .bmp file and write the framebuffer data into it

        // Define the BMP file header
        struct BMPHeader {
            uint16_t signature;   // BMP signature ("BM")
            uint32_t fileSize;    // Size of the BMP file
            uint32_t reserved;    // Reserved, set to 0
            uint32_t dataOffset;  // Offset to the pixel data
            uint32_t headerSize;  // Size of the header (40 bytes for BITMAPINFOHEADER)
            int32_t width;        // Width of the image
            int32_t height;       // Height of the image
            uint16_t planes;      // Number of color planes (always 1)
            uint16_t bpp;         // Bits per pixel (24 bits for RGB)
            uint32_t compression; // Compression method (0 for uncompressed)
            uint32_t dataSize;    // Size of the pixel data
            int32_t hResolution;  // Horizontal resolution (pixels per meter)
            int32_t vResolution;  // Vertical resolution (pixels per meter)
            uint32_t colors;      // Number of colors in the color palette (0 for no palette)
            uint32_t importantColors; // Number of important colors (0 when every color is important)
        };

        // Calculate the size of the pixel data
        uint32_t rowSize = WIDTH * BYTES_PER_PIXEL;
        uint32_t paddingSize = (4 - (rowSize % 4)) % 4;
        uint32_t dataSize = (rowSize + paddingSize) * HEIGHT;

        // Calculate the total file size
        uint32_t fileSize = sizeof(BMPHeader) + dataSize;

        // Create the BMP file header
        BMPHeader header;
        header.signature = 0x4D42; // BM
        header.fileSize = fileSize;
        header.reserved = 0;
        header.dataOffset = sizeof(BMPHeader);
        header.headerSize = 40; // Size of BITMAPINFOHEADER
        header.width = WIDTH;
        header.height = HEIGHT;
        header.planes = 1;
        header.bpp = BYTES_PER_PIXEL * 8;
        header.compression = 0;
        header.dataSize = dataSize;
        header.hResolution = 0;
        header.vResolution = 0;
        header.colors = 0;
        header.importantColors = 0;

        // Open the file for writing in binary mode
        std::ofstream file("output.bmp", std::ios::binary);

        // Write the BMP file header
        file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));

        // Generate a simple test pattern in the framebuffer
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                int index = y * WIDTH + x;
                uint8_t red = (x * 255) / (WIDTH - 1);
                uint8_t green = (y * 255) / (HEIGHT - 1);
                uint8_t blue = 128;

                framebuffer[index * BYTES_PER_PIXEL] = blue;
                framebuffer[index * BYTES_PER_PIXEL + 1] = green;
                framebuffer[index * BYTES_PER_PIXEL + 2] = red;
            }
        }

        // Write the pixel data
        for (int y = HEIGHT - 1; y >= 0; --y) {
            file.write(reinterpret_cast<char*>(framebuffer.data() + (y * rowSize)), rowSize);
            // Write padding bytes if necessary
            for (int p = 0; p < paddingSize; ++p) {
                file.put(0);
            }
        }

        // Close the file
        file.close();

        std::cout << "Framebuffer rendered to output.bmp." << std::endl;
    }
};

