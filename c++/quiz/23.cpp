// https://cppquiz.org/quiz/question/196
// https://en.wikipedia.org/wiki/Argument-dependent_name_lookup

#include <iostream>

namespace x {
  class C {};
  void f(const C& i) {
    std::cout << "1";
  }
}

namespace y {
  void f(const x::C& i) {
    std::cout << "2";
  }
}

int main() {
  f(x::C());  // 1 - WTF !!!!!
}