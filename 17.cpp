#include <array>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef vector<pair<double, int>> polynom;

const polynom POLYNOMIAL_1 = {{8.0, 6}, {5.0, 5}, {10.5, 4}, {-3.5, 3}, {15.0, 2}, {-1.0, 1}, {5.0, 0}};
const polynom POLYNOMIAL_2 = {{6.0, 3}, {-1.0, 1}};

// Информационная часть узла
struct Node {
    double coefficient;
    int degree;
    Node* next;

    Node(double coeff, int deg) : coefficient(coeff), degree(deg), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    // Проверка узлов в списке
    bool is_empty() { return first == nullptr; }

    // Вставка в конец - вспомогательная функция
    void push_back(double coeff, int deg) {
        Node* p = new Node(coeff, deg);
        if (is_empty()) {
            first = p;
            last = p;
        } else {
            last->next = p;
            last = p;
        }
    }

    // Вывод всего списка
    void print() {
        if (!is_empty()) {
            Node* p = first;
            while (p) {
                cout << p->coefficient << " " << p->degree << "   ";
                p = p->next;
            }
            cout << endl;
        } else
            cout << "Список пуст\n";
    }

    // Вывод многочлена из массива (вектора)
    void print_poly_from_vect(const polynom pol) {
        bool not_first_flag = false;
        for (auto num : pol) {
            if (not_first_flag && num.first >= 0) {
                cout << "+ " << num.first;
            } else {
                not_first_flag = true;
                if (num.first < 0)
                    cout << "- " << abs(num.first);
                else
                    cout << num.first;
            }
            if (num.second)
                cout << "x^" << num.second << " ";
        }
        cout << endl;
    }

    // Удалить в начале - вспомогательная функция
    void remove_first() {
        if (!is_empty()) {
            Node* p = first;
            first = p->next;
            delete p;
        } else
            cout << "Список пуст\n";
    }

    // Удалить в конце - вспомогательная функция
    void remove_last() {
        if (!is_empty()) {
            if (first != last) {
                Node* p = first;
                while (p->next != last) p = p->next;
                p->next = nullptr;
                delete last;
                last = p;
            } else
                remove_first();
        } else
            cout << "Список пуст\n";
    }

    // Удаление по заданному значению (по показателю степени)
    void remove(int deg) {
        if (!is_empty()) {
            if (first->degree == deg) {
                remove_first();
            } else if (last->degree == deg) {
                remove_last();
            } else {
                Node* prev = first;
                Node* curr = first->next;
                while (curr && curr->degree != deg) {
                    curr = curr->next;
                    prev = prev->next;
                }
                if (curr) {
                    prev->next = curr->next;
                    delete curr;
                } else {
                    cout << "Такого элементы не существует\n";
                }
            }
        } else
            cout << "Список пуст\n";
    }

    // Вывод многочлена в форме выражения
    void print_poly() {
        Node* p = first;
        if (!p) {
            cout << "0" << endl;
            return;
        }
        while (p) {
            if (p->degree)
                cout << abs(p->coefficient) << "x^" << p->degree;
            else cout << abs(p->coefficient);
            p = p->next;
            if (p) {
                cout << " ";
                if (p->coefficient >= 0)
                    cout << "+ ";
                else
                    cout << "- ";
            }
        }
        cout << endl;
    }

    // Вычисление значения
    void counter() {
        cout << "Введите значение х: ";
        double x;
        cin >> x;
        Node* curr = first;
        double result = 0;
        for (int deg = curr->degree; deg >= 0; --deg) {
            if (curr && curr->degree == deg) {
                result = result * x + curr->coefficient;
                curr = curr->next;
            } else {
                result = result * x;
            }
        }
        cout << "Результат при х=" << x << ": " << result << "\n";
    }

    // Вставка узла перед первым узлом
    void insert(double coeff, int deg) {
        Node* newNode = new Node(coeff, deg);
        newNode->next = first;
        first = newNode;
    }

    // Очистка памяти
    void clearList() {
        Node* temp;
        while (first) {
            temp = first;
            first = first->next;
            delete temp;
        }
    }

    // Многочлен из массива
    void initializePolynomial(polynom polynomial) {
        for (auto item : polynomial) {
            push_back(item.first, item.second);
        }
    }

    // Создание списка вручную
    void manual_create() {
        cout << endl;
        bool confirmed = false;
        char confirm;
        if (!is_empty()) {
            cout << "Многочлен уже существует. Жалеаете его пересоздать? (y/n): ";
            cin >> confirm;
            switch (confirm) {
                case 'y':
                    clearList();
                    confirmed = true;
                    break;

                case 'n':
                    break;

                default:
                    cout << "Проверьте ввод\n";
                    cin.clear();
            }
        } else
            confirmed = true;

        if (confirmed) {
            cout << "Начните ввод с показателя степени старшего члена. Затем вводите коэффициенты для всех "
                    "младших членов.\n";
            cout << "Чтобы пропустить текущий член, введите 0\n";
            polynom user_poly;
            int input_deg = 0;
            double input_coeff;
            while (input_deg <= 0) {
                cout << "Введите показатель степени старшего члена: ";
                cin >> input_deg;
            }
            for (int i = input_deg; i >= 0; --i) {
                cout << "Введите коэффициент для члена с показетелем степени " << i << ": ";
                cin >> input_coeff;
                if (input_coeff) {
                    user_poly.push_back(make_pair(input_coeff, i));
                    cout << "Добавлено: " << input_coeff << "x^" << i << endl;
                }
            }
            initializePolynomial(user_poly);
            cout << "Многочлен создан\n";
        }
    }

    // создание списка на основе готового
    void create() {
        char choose;
        bool confirmed = false;

        if (!is_empty()) {
            char confirm;
            cout << "Многочлен уже существует. Жалеаете его пересоздать? (y/n): ";
            cin >> confirm;
            switch (confirm) {
                case 'y':
                    clearList();
                    confirmed = true;
                    break;

                case 'n':
                    break;

                default:
                    cout << "Проверьте ввод\n";
                    cin.clear();
            }
        } else
            confirmed = true;

        if (confirmed) {
            cout << "Выберите многочлен: \n";
            cout << "1. ";
            print_poly_from_vect(POLYNOMIAL_1);
            cout << "2. ";
            print_poly_from_vect(POLYNOMIAL_2);

            bool choosing = true;
            while (choosing) {
                cin >> choose;
                switch (choose) {
                    case '1':
                        initializePolynomial(POLYNOMIAL_1);
                        choosing = false;
                        break;
                    case '2':
                        initializePolynomial(POLYNOMIAL_2);
                        choosing = false;
                        break;
                    default:
                        cout << "Неверный выбор. Попробуйте снова.\n";
                }
            }
            cout << "Список успешно создан!\n";
        }
    }
};

void ind_func_menu() {
    cout << endl;
    cout << "1. Создать список вручную\n";
    cout << "2. Вывести многочлен в виде выражения\n";
    cout << "3. Вычислить значение многочлена\n";
    cout << "0. Назад\n";
    cout << "Выш выбор: ";
}

void ind_choose(list* head_ptr) {
    char choose;
    bool func_flag = true;

    while (func_flag) {
        ind_func_menu();
        cin >> choose;
        switch (choose) {
            case '1':
                head_ptr->manual_create();
                break;

            case '2':
                head_ptr->print_poly();
                break;

            case '3':
                if (!head_ptr->is_empty())
                    head_ptr->counter();
                else
                    cout << "\nСписок пуст. Для вычисления значения многочлена создайте его.\n";
                break;

            case '0':
                cout << endl;
                func_flag = false;
                break;
            default:
                cout << "Проверьте введённые данные\n";
                cin.clear();
        }
    }
}

void comm_func_menu() {
    cout << endl;
    cout << "1. Вставка узла в начало списка\n";
    cout << "2. Удаление узла по ключу (по показателю степени)\n";
    cout << "3. Создание списка на основе готового\n";
    cout << "4. Вывести raw-список в консоль\n";
    cout << "0. Назад\n";
    cout << "Выш выбор: ";
}

void comm_choose(list* head_ptr) {
    char choose;
    bool func_flag = true;

    while (func_flag) {
        double coeff;
        int degree;
        comm_func_menu();
        cin >> choose;
        switch (choose) {
            case '1':
                cout << "\nВыбрана функция вставки узла в начало списка\n";
                coeff = 0;
                degree = -1;
                while (!coeff) {
                    cout << "Введите коэффициент: ";
                    cin >> coeff;
                    cout << endl;
                    cin.clear();
                }
                while (degree < 0) {
                    cout << "Введите показатель степени: ";
                    cin >> degree;
                    cout << endl;
                    cin.clear();
                    if (degree <= head_ptr->first->degree) {
                        cout << "Показатель степени должен превышать текущий наибольший\n";
                        degree = -1;
                    }
                }
                head_ptr->insert(coeff, degree);
                cout << "Узел успешно вставлен.\n";
                break;

            case '2':
                cout << "\nВыбрана функция удаления узла по ключу\n";
                degree = -1;
                while (degree < 0) {
                    cout << "Введите показатель степени для удаления: ";
                    cin >> degree;
                    cout << endl;
                }
                head_ptr->remove(degree);
                cout << "Узел с показателем степени " << degree << " успешно удалён.\n";
                break;

            case '3':
                cout << "\nВыбрана функция создания списка на основе готового\n";
                head_ptr->create();
                break;

            case '4':
                cout << "\nВыбрана функция вывода raw-списка\n";
                head_ptr->print();
                break;

            case '0':
                cout << endl;
                func_flag = false;
                break;

            default:
                cout << "Проверьте введённые данные\n";
                cin.clear();
        }
    }
}

void start_menu() {
    cout << "1. Индивидуальные функции\n";
    cout << "2. Общие функции\n";
    cout << "0. Выход из программы\n";
    cout << "Выш выбор: ";
}

int main() {
    list head;
    char choice;
    bool working_flag = true;

    while (working_flag) {
        start_menu();
        cin >> choice;
        switch (choice) {
            case '1':
                ind_choose(&head);
                break;

            case '2':
                comm_choose(&head);
                break;

            case '0':
                working_flag = false;
                head.clearList();
                break;

            default:
                cout << "Проверьте введённые данные\n";
                cin.clear();
        }
    }
    return 0;
}