#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
    int n1, m1; // размерность первой матрицы
    int n2, m2; // размерность второй матрицы
    cout << "Enter n1, m1: ";
    cin >> n1 >> m1; // считываем размерность первой матрицы
    cout << "Enter n2, m2: ";
    cin >> n2 >> m2; // считываем размерность второй матрицы

    // создаём матрицы
    Matrix a(n1, m1);
    Matrix b(n2, m2);

    cout << endl << "Read matrix A:" << endl;
    a.Read();
    cout << endl << "Read matrix B:" << endl;
    b.Read();

    cout << "Created matrices:" << endl;
    cout << "Matrix A:" << endl;
    a.Print();
    cout << "Matrix B:" << endl;
    b.Print();

    cout << endl;
    cout << "A == B: " << (a == b ? "yes" : "no") << endl;
    cout << "A != B: " << (a != b ? "yes" : "no") << endl;
    cout << "A < B: " << (a < b ? "yes" : "no") << endl;
    cout << "A > B: " << (a > b ? "yes" : "no") << endl;

    cout << endl;

    try {
        cout << "A + B:" << endl;
        Matrix sum = a + b;
        sum.Print();
    }
    catch (const exception& error) {
        cout << error.what() << endl; // выводим ошибку
    }

    try {
        cout << "A - B:" << endl;
        Matrix sub = a - b;
        sub.Print();
    }
    catch (const exception& error) {
        cout << error.what() << endl; // выводим ошибку
    }

    try {
        Matrix mult = a * b;
        cout << "A * B:" << endl;
        mult.Print();
    }
    catch (const exception& error) {
        cout << error.what() << endl; // выводим ошибку
    }

    cout << endl;
    cout << "A * 5:" << endl;
    (a * 5).Print();
    cout << "-2.5 * A:" << endl;
    (-2.5 * a).Print();
    cout << "B / 2:" << endl;
    (b / 2).Print();
    cout << "++A:" << endl;
    (++a).Print();
    cout << "--B:" << endl;
    (--b).Print();

}