// #include "Framebuffer.cpp"

// int main() {
//     Framebuffer framebuffer;

//     framebuffer.clear();

//     framebuffer.renderBuffer();

//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <FreeImage.h>
// #include <X11/Xlib.h>
// using namespace std;

// vector<Color> framebuffer; // Global variable representing the framebuffer
// Color clearColor(0, 0, 0);

// void clear() {
//   framebuffer.assign(framebuffer.size(), clearColor);
//   // std::fill(framebuffer.begin(), framebuffer.end(), clearColor);
// }

// void saveFramebufferImage() {
//   FreeImage_Initialise();

//   // Create a new FreeImage bitmap
//   FIBITMAP* bitmap = FreeImage_Allocate(framebuffer.size(), 1, 24);

//   // Set the color values in the bitmap
//   RGBQUAD color;
//   for (int i = 0; i < framebuffer.size(); ++i) {
//     const Color& pixelColor = framebuffer[i];
//     color.rgbRed = static_cast<BYTE>(pixelColor.red);
//     color.rgbGreen = static_cast<BYTE>(pixelColor.green);
//     color.rgbBlue = static_cast<BYTE>(pixelColor.blue);
//     FreeImage_SetPixelColor(bitmap, i, 0, &color);
//   }

//   // Save the bitmap as an image file
//   FreeImage_Save(FIF_PNG, bitmap, "framebuffer.png", 0);

//   // Free resources
//   FreeImage_Unload(bitmap);
//   FreeImage_DeInitialise();
// }

// int main() {
//   Color color1(10, 0, 111);
//   Color color2(200, 105, 0);
//   Color color3 = colorAddition(color1, color2);
//   Color color4 = floatTimesColor(1.5, color1);

//   cout << "The RGB1 is: " << static_cast<int>(color1.red) << " " << static_cast<int>(color1.green) << " " << static_cast<int>(color1.blue);
//   printf("\n");
//   cout << "The RGB2 is: " << static_cast<int>(color2.red) << " " << static_cast<int>(color2.green) << " " << static_cast<int>(color2.blue);
//   printf("\n");
//   cout << "The RGB3 is: " << static_cast<int>(color3.red) << " " << static_cast<int>(color3.green) << " " << static_cast<int>(color3.blue);
//   printf("\n");
//   cout << "The RGB4 is: " << static_cast<int>(color4.red) << " " << static_cast<int>(color4.green) << " " << static_cast<int>(color4.blue);
//   printf("\n");

//   // Display* display = XOpenDisplay(NULL);
//   // Screen* screen = DefaultScreenOfDisplay(display);
//   // int framebufferWidth = screen->width;
//   // int framebufferHeight = screen->height;

//   // // framebuffer.resize(framebufferWidth, vector<Color>(framebufferHeight));
//   // int totalPixels = framebufferWidth * framebufferHeight;
//   // framebuffer.resize(totalPixels, clearColor);
//   // clear();

//   // saveFramebufferImage();
//   // XCloseDisplay(display);

//   return 0;
// }

// #include <iostream>
// #include <vector>
// #include <FreeImage.h>
// #include <X11/Xlib.h>

// using namespace std;

// class Color
// {
// public:
//     int red;
//     int green;
//     int blue;
//     Color(int r, int g, int b) : red(r), green(g), blue(b) {}
// };

// vector<Color> framebuffer;
// Color clearColor(0, 0, 0);

// void clear()
// {
//     framebuffer.assign(framebuffer.size(), clearColor);
// }

// void saveFramebufferImage(int framebufferWidth, int framebufferHeight)
// {
//     FreeImage_Initialise();

//     // Create a new FreeImage bitmap
//     FIBITMAP *bitmap = FreeImage_Allocate(framebufferWidth, framebufferHeight, 24);

//     // Set the color values in the bitmap
//     RGBQUAD color;
//     for (int y = 0; y < framebufferHeight; ++y)
//     {
//         for (int x = 0; x < framebufferWidth; ++x)
//         {
//             const Color &pixelColor = framebuffer[y * framebufferWidth + x];
//             color.rgbRed = static_cast<BYTE>(pixelColor.red);
//             color.rgbGreen = static_cast<BYTE>(pixelColor.green);
//             color.rgbBlue = static_cast<BYTE>(pixelColor.blue);
//             FreeImage_SetPixelColor(bitmap, x, y, &color);
//         }
//     }

//     // Save the bitmap as a PNG image
//     FreeImage_Save(FIF_PNG, bitmap, "framebuffer.png", PNG_DEFAULT);

//     // Free resources
//     FreeImage_Unload(bitmap);
//     FreeImage_DeInitialise();
// }

// int main()
// {
//     Display *display = XOpenDisplay(NULL);
//     Screen *screen = DefaultScreenOfDisplay(display);
//     int framebufferWidth = screen->width;
//     int framebufferHeight = screen->height * 2;

//     framebuffer.resize(framebufferWidth * framebufferHeight, clearColor);
//     clear();
//     saveFramebufferImage(framebufferWidth, framebufferHeight);

//     XCloseDisplay(display);

//     return 0;
//     }

    
#include <iostream>
#include <vector>
#include "Color.cpp"

    const int BUFFER_WIDTH = 700;
    const int BUFFER_HEIGHT = 500;

    // Function to draw a point at the center of the buffer
    void drawPointInCenter(std::vector<Color>& buffer, const Color& color) {
        int centerX = BUFFER_WIDTH / 2;
        int centerY = BUFFER_HEIGHT / 2;
        int index = centerY * BUFFER_WIDTH + centerX;
        buffer[index] = color;
    }

    // Function to render the buffer to the console
    void renderBuffer(const std::vector<Color>& buffer) {
        for (int y = 0; y < BUFFER_HEIGHT; ++y) {
            for (int x = 0; x < BUFFER_WIDTH; ++x) {
                std::cout << "(" << buffer[y * BUFFER_WIDTH + x].getRed() << ","
                          << buffer[y * BUFFER_WIDTH + x].getGreen() << ","
                          << buffer[y * BUFFER_WIDTH + x].getBlue() << ")";
            }
            std::cout << std::endl;
        }
    }

    int main() {
        std::vector<Color> buffer(BUFFER_WIDTH * BUFFER_HEIGHT, Color(0, 0, 0));

        // Draw a point in the center of the buffer
        Color centerColor(255, 0, 0); // Red color
        // drawPointInCenter(buffer, centerColor);

        // Render the buffer
        renderBuffer(buffer);

        return 0;
    }
