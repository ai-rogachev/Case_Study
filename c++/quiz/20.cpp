// https://cppquiz.org/quiz/question/118

#include <iostream>

void print(char const *str) { std::cout << str; }
void print(short num) { std::cout << num; }

int main() {
  print("abc");
  print(0);
  print('A');
}