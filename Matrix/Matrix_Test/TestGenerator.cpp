#include <cmath>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <iomanip>

void rand_fill(int** start, int r, int c, int len) {
    if (len <= 2)
        return;
    if (rand() % 2) {
        for (int i = 0; i < len / 2; i++)
            for (int j = len / 2; j < len; j++)
                start[r + i][c + j] = rand() % 21 - 10;
    }
    else {
        for (int i = 0; i < len / 2; i++)
            for (int j = len / 2; j < len; j++)
                start[r + j][c + i] = rand() % 21 - 10;
    }
    rand_fill(start, r, c, len / 2);
    rand_fill(start, r + len / 2, c + len / 2, len / 2);
}

int main()
{
    std::srand(getpid());
    int block_derp = std::rand() % 7 + 1;
    int matrix_size = std::pow(2, block_derp);
    std::cout << matrix_size << "\n";

    int** matrix = new int*[matrix_size];
    for (int i = 0; i < matrix_size; i++)
        matrix[i] = new int[matrix_size];

    std::vector<int> sub_dep(matrix_size / 2, 0);
    int max_dep = 10000000;
    int det = 1;
    for (int i = 0; i < matrix_size / 2; i++) {
        int d = 0;
        while ((d = std::rand() % std::min(21, 2 * max_dep + 1) - std::min(10, max_dep)) == 0) ;
        sub_dep[i] = d;
        max_dep /= std::abs(sub_dep[i]);
        //std::cout << sub_dep[i] << " ";
        det *= sub_dep[i];
    }
    //std::cout << "\n";
    for (int i = 0; i < matrix_size / 2; i++) {
        std::vector<int> del1, del2;
        int bc = std::rand() % 21 - 10;
        for (int d = 1; d < std::abs(bc); d++) {
            if (std::abs(bc) % d == 0)
                del1.push_back(d);
        }
        for (int d = 1; d < std::abs(sub_dep[i] + bc); d++) {
            if (std::abs(sub_dep[i] + bc) % d == 0)
                del2.push_back(d);
        }
        int a, b, c, d;
        if (del1.size() == 0) {
            if (std::rand() % 2) {
                b = 1;
                c = bc;
            }
            else {
                b = bc;
                c = 1;
            }
        }
        else {
            b = del1[std::rand() % del1.size()];
            c = bc / b;
        }

        if (del2.size() == 0) {
            if (std::rand() % 2) {
                a = 1; 
                d = sub_dep[i] + bc;
            }
            else {
                a = sub_dep[i] + bc;
                d = 1;
            }
        }
        else {
            a = del2[std::rand() % del2.size()];
            d = (sub_dep[i] + bc) / a;
        }
        //std::cout << a << std::setw(5) << b << "\n" << c << std::setw(5) << d << "\n\n";
        matrix[2 * i][2 * i] = a;
        matrix[2 * i][2 * i + 1] = b;
        matrix[2 * i + 1][2 * i] = c;
        matrix[2 * i + 1][2 * i + 1] = d;
    }

    rand_fill(matrix, 0, 0, matrix_size);

    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++)
            std::cout << matrix[i][j] << std::setw(5);
        std::cout << "\n";
    }

    std::cout << det << "\n";

    return 0;
}