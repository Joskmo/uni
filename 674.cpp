#include <iostream>

using namespace std;

int main() {
    int size;
    cout << "Введите размер для квадратичной матрицы: "
    if (cin >> size && size > 0) { 

        int** matrix = new *int[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << "Введите элемент с индексом " << i << " " << j << ":";
                while (!(cin >> matrix[i][j])) {
                    cout << "Ошибка. Проверьте введённые данные\n";
                }
            }
        }

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << "\n";
        }
    } else {
        cout << "Ошибка. Проверьте введённые данные\n";
    }
}