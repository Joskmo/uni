/* Задача 630a
Дана действительная матрица размера n*m.
Упорядочить строки матрицы по неубыванию значений первых элементов строк.
*/

#include <cstdlib>
#include <iostream>
#include <climits>
#include <string>
#include <cmath>

void matrix_sort(int** matrix, int n, int m);
void matrix_print(int** matrix, int n, int m, int max_num);
void randomMatrix();
void manualMatrix();
int validator();
int get_lenth(int num);

int main(int argc, char* argv[]) {
    if ((argc == 2) && (std::string(argv[1]) == "rand"))
        randomMatrix();
    else
        manualMatrix();
    return 0;
}

void manualMatrix() {
    int m, n;
    std::cout << "Введите размерность матрицы N на M: ";
    n = validator();
    m = validator();
    if (m > 0 && n > 0) {
        int max_len;
        int** matrix = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) matrix[i] = (int*)malloc(m * sizeof(int));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                std::cout << "Введите значения для элемента с индексами " << i + 1 << " " << j + 1 << ": ";
                matrix[i][j] = validator();
                if (!i && !j) max_len = get_lenth(matrix[i][j]);
                if (get_lenth(matrix[i][j]) > max_len) max_len = get_lenth(matrix[i][j]);
            }
        matrix_sort(matrix, n, m);
        std::cout << "\nОтсортированная матрица:\n";

        // Выводим матрицу:
        matrix_print(matrix, n, m, max_len);
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);
    } else
        std::cout << "n/a\n";
}

void randomMatrix() {
    std::cout << "Матрица будет заполнена случайными значениями и выдан случайный размер\n";
    int m, n;
    n = rand() % 20 + 1;
    m = rand() % 20 + 1;
    std::cout << "Размеры матрицы: " << n << " на " << m << "\n"
              << "Исходная матрица:\n";
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) matrix[i] = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 101 - 50;  // заполняем матрицу случайными числами в даиапазоне [-50; +50]
    matrix_print(matrix, n, m, 3);
    matrix_sort(matrix, n, m);
    std::cout << "\nОтсортированная матрица:\n";
    matrix_print(matrix, n, m, 3);
    for (int i = 0; i < n; i++) free(matrix[i]);
    free(matrix);
}

void matrix_sort(int** matrix, int n, int m) {
    int* bubble = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n - i - 1; k++)
            if (matrix[k][0] > matrix[k + 1][0])
                for (int j = 0; j < m; j++) {
                    bubble[j] = matrix[k + 1][j];
                    matrix[k + 1][j] = matrix[k][j];
                    matrix[k][j] = bubble[j];
                }
    free(bubble);
}

void matrix_print(int** matrix, int n, int m, int max_num_lenth) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int count = get_lenth(matrix[i][j]); count <= max_num_lenth; count++) std::cout << " ";
            std::cout << " " << matrix[i][j];
        }
        std::cout << "\n";
    }
}

int validator() { // проверка ввода
    bool err = true;
    int output = 0;
    while (err) {
        err = false;
        std::string input;
        int test = 0;
        try {
            std::cin >> input;
            for (size_t i = 0; i < input.size(); i++) {
                test = (((int)input[i] > 47 && (int)input[i] < 58) || (int)input[i] == 45);
                if (!test) {
                    std::cout << "Проверьте введённые данные\n";
                    err = true;
                    break;
                } else {
                    output = std::stoi(input);
                }
            }
            // if (minus) output *= -1;
        }
        catch (...) {
            err = true;
            std::cout << "Проверьте введённые данные\n";
        }
    }
    return output;
}

int get_lenth(int num) {
    int len = 1;
    if (num > 0) len = static_cast<int>(std::log10(num)) + 1;
    else if (num) len = static_cast<int>(std::log10(num * (-1))) + 2;
    return len;
}