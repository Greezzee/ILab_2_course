#include "../Matrix_Source/Matrix.h"
#include <iostream>
int main() {
    int size;
    std::cin >> size;

    matrix::Matrix<int> test(size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            std::cin >> test[i][j];
    int right_answer;
    std::cin >> right_answer;

    int answer = test.Determinant();

    if (answer == right_answer)
        std::cout << "OK\n";
    else
    {
        std::cout << "Incorrect answer. " << right_answer << " expected, " << answer << " calculated\n";
    }
    return 0;
}