#include <iostream>

#include "Matrix.h"

int main()
{
    using mat2d_t = Matrix<int, 0>;
    mat2d_t mat;

    // Заполнение матрицы.
    for (size_t i = 0; i < 10; ++i) {
        mat[i][i] = static_cast<int>(i);
        mat[i][9 - i] = static_cast<int>(i);
    }

    // Вывод значений.
    std::cout << "Matrix values: " << std::endl;
    for (size_t i = 1; i < 9; ++i) {
        for (size_t j = 1; j < 9; ++j)
            std::cout << mat[i][j] << " ";
        std::cout << std::endl;
    }
    return 0;
}