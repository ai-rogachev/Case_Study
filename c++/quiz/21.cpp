// https://cppquiz.org/quiz/question/179

/*
Modifying a const object results in undefined behavior. Casting away constness does not help.

§[dcl.type.cv]¶4 in the standard:

    Any attempt to modify a const object during its lifetime (3.8) results in undefined behavior
*/
 
#include <iostream>

int main() {
    const int i = 0;
    int& r = const_cast<int&>(i);
    r = 1;
    std::cout << r;
}