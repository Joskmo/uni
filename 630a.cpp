/* Задача 630a
Дана действительная матрица размера n*m.
Упорядочить строки матрицы по неубыванию значений первых элементов строк.
*/

#include <cstdlib>
#include <iostream>
#include <string>

void matrix_input(int** matrix, int n, int m);
void matrix_sort(int** matrix, int n, int m);
void matrix_print(int** matrix, int n, int m);
void rand_inp(int** matrix, int n, int m);

int main(int argc, char* argv[]) {
    bool randFlag = false;
    if (argc == 2) if(std::string(argv[1]) == "rand") {
        randFlag = true;
        std::cout << "Матрица будет заполнена случайными значениями и выдан случайный размер\n";
    }
    // Проверка на флаг rand, для случайного заполнения матрицы

    int m, n;
    if (randFlag) {
        n = rand() % 20 + 1;
        m = rand() % 20 + 1;
        std::cout << "Размеры матрицы: " << n << " на " << m << "\n" << "Исходная матрица:\n";
    } else {
        std::cout << "Введите размерность матрицы N на M: ";
        std::cin >> n >> m;
    }

    if (m > 0 && n > 0) {
        // Выделяем память под матрицу:
        int** matrix = (int**)malloc(n * sizeof(int*));
        for (int i = 0; i < n; i++) matrix[i] = (int*)malloc(m * sizeof(int));

        if (randFlag) {  // случайно заполняем матрицу
            rand_inp(matrix, n, m);
            matrix_print(matrix, n, m);
        } else
            matrix_input(matrix, n, m);  // Заполняем матрицу вручную

        // Сортируем матрицу:
        matrix_sort(matrix, n, m);

        std::cout << "\nОтсортированная матрица:\n";
        // Выводим матрицу:
        matrix_print(matrix, n, m);

        // Очищаем память:
        for (int i = 0; i < n; i++) {
            free(matrix[i]);
        }
        free(matrix);

    } else
        std::cout << "n/a\n";
    return 0;
}

void matrix_input(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << "Введите значения для элемента с индексами " << i + 1 << " " << j + 1 << ": ";
            std::cin >> matrix[i][j];
        }
    }
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

void matrix_print(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) std::cout << matrix[i][j] << " ";
        std::cout << "\n";
    }
}

void rand_inp(int** matrix, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 101 - 50;  // заполняем матрицу случайными числами в даиапазоне [-50; +50]
        }
}