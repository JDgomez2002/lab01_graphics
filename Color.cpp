#include <iostream>
using namespace std;

class Color {
  public:
    // Color() : red(0), green(0), blue(0) {}
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

  private:
    int red;
    int green;
    int blue;
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
  int newRed = colorClamping(a.getRed() + b.getRed());
  int newGreen = colorClamping(a.getGreen() + b.getGreen());
  int newBlue = colorClamping(a.getBlue() + b.getBlue());
  Color newColor(newRed, newGreen, newBlue);
  return newColor;
}

Color floatTimesColor(float n, Color color){
  int newRed = colorClamping(static_cast<int> (n * color.getRed()));
  int newGreen = colorClamping(static_cast<int> (n * color.getGreen()));
  int newBlue = colorClamping(static_cast<int> (n * color.getBlue()));
  Color newColor(newRed, newGreen, newBlue);
  return newColor;
}
