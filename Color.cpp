#include <iostream>
using namespace std;

class Color {
  public:
    int red;
    int green;
    int blue;
    Color() : red(0), green(0), blue(0) {}
    Color(int r, int g, int b);

    int getRed() const {
        return red;
    }

    int getGreen() const {
        return green;
    }

    int getBlue() const {
        return blue;
    }
};

int colorClamping(int value){
  if(value>255){
    return 255;
  }
  else if(value<0){
    return 0;
  }
  else {
    return value;
  }
}

Color::Color(int r, int g, int b){
  red = colorClamping(r);
  green = colorClamping(g);
  blue = colorClamping(b);
}

Color colorAddition(Color a, Color b) {
  int newRed = colorClamping(a.red + b.red);
  int newGreen = colorClamping(a.green + b.green);
  int newBlue = colorClamping(a.blue + b.blue);
  Color newColor(newRed, newGreen, newBlue);
  return newColor;
}

Color floatTimesColor(float n, Color color){
  int newRed = colorClamping(static_cast<int> (n * color.red));
  int newGreen = colorClamping(static_cast<int> (n * color.green));
  int newBlue = colorClamping(static_cast<int> (n * color.blue));
  Color newColor(newRed, newGreen, newBlue);
  return newColor;
}
