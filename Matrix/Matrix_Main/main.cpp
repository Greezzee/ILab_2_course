#include "../Matrix_Source/Matrix.h"
#include <iostream>
int main() {
    int size;
    std::cin >> size;

    matrix::Matrix<int> test(size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            std::cin >> test[i][j];
    std::cout << test.Determinant() << "\n";
    return 0;
}