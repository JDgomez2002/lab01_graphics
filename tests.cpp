#include <iostream>
using namespace std;

int main() {
  int a = 10;
  float b = 1.52;

  std::cout << static_cast<float> (a*b);
  printf("\n");

  return 0;
}