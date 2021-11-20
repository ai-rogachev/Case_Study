// https://cppquiz.org/quiz/question/148

#include <iostream>

volatile int a;

int main() {
  std::cout << (a + a);
}