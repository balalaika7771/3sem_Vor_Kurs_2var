#pragma once

#include <iostream>
#include <iomanip>


class Matrix {
    double **values; // значения
    int n; // число строк
    int m; // число столбцов

public:
    Matrix(int n = 1, int m = 1); // конструктор произвольной матрицы
    Matrix(const Matrix& matrix); // конструктор копирования

    Matrix& operator=(const Matrix& matrix); // оператор присваивания

    void Print() const; // вывод матрицы
    void Read(); // ввод матрицы

    double& operator()(int i, int j); // получение элемента по индексам
    double operator()(int i, int j) const; // получение элемента по индексам

    bool operator==(const Matrix& matrix) const; // проверка на равенство
    bool operator!=(const Matrix& matrix) const; // проверка на неравенство
    bool operator<(const Matrix& matrix) const; // проверка на меньше
    bool operator>(const Matrix& matrix) const; // проверка на больше

    Matrix operator+(const Matrix& matrix) const; // сложение матриц
    Matrix operator-(const Matrix& matrix) const; // разность матриц
    Matrix operator*(const Matrix& matrix) const; // умножение матриц

    Matrix& operator+=(const Matrix& matrix); // прибавление матрицы
    Matrix& operator-=(const Matrix& matrix); // вычитание матрицы

    Matrix operator++(int); // постинкремент
    Matrix operator--(int); // постдекремент
    Matrix& operator++(); // преинкремент
    Matrix& operator--(); // предекремент

    Matrix operator*(double scalar) const; // умножение матрицы на скаляр
    friend Matrix operator*(double scalar, const Matrix& matrix); // умножение матрицы на скаляр
    Matrix operator/(double scalar) const; // деление матрицы на скаляр

    ~Matrix(); // деструктор, освобождение памяти
};

// конструктор произвольной матрицы
Matrix::Matrix(int n, int m) {
    this->n = n; // сохраняем число строк
    this->m = m; // сохраняем число столбцов

    // выделяем память под элементы матрицы и обнуляем их
    values = new double*[n];

    for (int i = 0; i < n; i++) {
        values[i] = new double[m];

        for (int j = 0; j < m; j++)
            values[i][j] = 0;
    }
}

// конструктор копирования
Matrix::Matrix(const Matrix& matrix) {
    n = matrix.n;
    m = matrix.m;

    // выделяем память под элементы матрицы и копируем значения из матрицы
    values = new double*[n];

    for (int i = 0; i < n; i++) {
        values[i] = new double[m];

        for (int j = 0; j < m; j++)
            values[i][j] = matrix.values[i][j];
    }
}

// оператор присваивания
Matrix& Matrix::operator=(const Matrix& matrix) {
    if (this == &matrix)
        return *this; // нет смысла в присваивании самому себе

    // освобождаем память от текущей матрицы
    for (int i = 0; i < n; i++)
        delete[] values[i];

    delete[] values; // освобождаем память из-под строк

    n = matrix.n; // сохраняем число строк
    m = matrix.m; // сохраняем число столбцов

    // выделяем память под элементы матрицы и копируем значения из матрицы
    values = new double*[n];

    for (int i = 0; i < n; i++) {
        values[i] = new double[m];

        for (int j = 0; j < m; j++)
            values[i][j] = matrix.values[i][j];
    }

    return *this;
}

// вывод матрицы в поток
void Matrix::Print() const {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << std::setw(8) << values[i][j] << " ";

        std::cout << std::endl;
    }
}

// ввод матрицы
void Matrix::Read() {
    for (int i = 0; i < n; i++) {
        std::cout << "Enter row " << (i + 1) << ": ";

        for (int j = 0; j < m; j++)
            std::cin >> values[i][j];
    }
}

// получение элемента по индексам
double& Matrix::operator()(int i, int j) {
    return values[i][j];
}

// получение элемента по индексам
double Matrix::operator()(int i, int j) const {
    return values[i][j];
}

// проверка матриц на равенство
bool Matrix::operator==(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        return false; // матрицы не равны, если не равны их размеры

    // если хотя бы один элемент не совпадает, матрицы не равны
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (values[i][j] != matrix.values[i][j])
                return false;

    return true; // если дошли, то матрицы равны
}

// проверка матриц на неравенство
bool Matrix::operator!=(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        return true; // матрицы не равны, если не равны их размеры

    // если хотя бы один элемент не совпадает, матрицы не равны
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (values[i][j] != matrix.values[i][j])
                return true;

    return false; // если дошли, то матрицы равны
}

// проверка матриц на меньше
bool Matrix::operator<(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        return false; // матрицы не сравнимы, если не равны их размеры

    // если хотя бы один элемент больше или равен, матрица не меньше
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (values[i][j] >= matrix.values[i][j])
                return false;

    return true; // если дошли, то матрица меньше
}

// проверка матриц на больше
bool Matrix::operator>(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        return false; // матрицы не сравнимы, если не равны их размеры

    // если хотя бы один элемент меньше или равен, матрица не больше
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (values[i][j] <= matrix.values[i][j])
                return false;

    return true; // если дошли, то матрица больше
}

// сложение матриц
Matrix Matrix::operator+(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        throw std::runtime_error("Matrix::operator+: invalid sizes"); // бросаем исключение, если нельзя найти сумму матриц

    Matrix result(n, m); // создаём матрицу для результата

    // считаем сумму значений элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result.values[i][j] = values[i][j] + matrix.values[i][j];

    return result; // возвращаем полученную матрицу
}

// разность матриц
Matrix Matrix::operator-(const Matrix& matrix) const {
    if (n != matrix.n || m != matrix.m)
        throw std::runtime_error("Matrix::operator-: invalid sizes"); // бросаем исключение, если нельзя найти разность матриц

    Matrix result(n, m); // создаём матрицу для результата

    // считаем разность значений элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result.values[i][j] = values[i][j] - matrix.values[i][j];

    return result; // возвращаем полученную матрицу
}

// умножение матриц
Matrix Matrix::operator*(const Matrix& matrix) const {
    if (m != matrix.n)
        throw std::runtime_error("Matrix::operator*: invalid sizes"); // бросаем исключение, если нельзя найти произведение матриц

    Matrix result(n, matrix.m); // создаём матрицу для результата

    // вычисляем произведение матриц
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < matrix.m; j++) {
            double sum = 0;

            for (int k = 0; k < m; k++)
                sum += values[i][k] * matrix.values[k][j];

            result.values[i][j] = sum;
        }
    }

    return result; // возвращаем полученную матрицу
}

// прибавление матрицы
Matrix& Matrix::operator+=(const Matrix& matrix) {
    if (n != matrix.n || m != matrix.m)
        throw std::runtime_error("Matrix::operator+=: invalid sizes"); // бросаем исключение, если нельзя найти сумму матриц

    // считаем сумму значений элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j] += matrix.values[i][j];

    return *this; // возвращаем матрицу
}

// вычитание матрицы
Matrix& Matrix::operator-=(const Matrix& matrix) {
    if (n != matrix.n || m != matrix.m)
        throw std::runtime_error("Matrix::operator-=: invalid sizes"); // бросаем исключение, если нельзя найти сумму матриц

    // считаем разность значений элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j] -= matrix.values[i][j];

    return *this; // возвращаем матрицу
}

// постинкремент
Matrix Matrix::operator++(int) {
    Matrix result(*this); // копируем матрицу

    // обновляем значения элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j]++;

    return result; // возвращаем исходную копию
}

// постдекремент
Matrix Matrix::operator--(int) {
    Matrix result(*this); // копируем матрицу

    // обновляем значения элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j]--;

    return result; // возвращаем исходную копию
}

// преинкремент
Matrix& Matrix::operator++() {
    // обновляем значения элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j]++;

    return *this; // возвращаем исходную копию
}

// предекремент
Matrix& Matrix::operator--() {
    // обновляем значения элементов
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            values[i][j]--;

    return *this; // возвращаем исходную копию
}

// умножение матрицы на скаляр
Matrix Matrix::operator*(double scalar) const {
    Matrix result(n, m); // создаём матрицу для результата

    // умножаем каждый элемент матрицы на скаляр и записываем его в результирующую матрицу
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result.values[i][j] = values[i][j] * scalar;

    return result; // возвращаем полученную матрицу
}

// умножение матрицы на скаляр
Matrix operator*(double scalar, const Matrix& matrix) {
    return matrix * scalar;
}

// деление матрицы на скаляр
Matrix Matrix::operator/(double scalar) const {
    Matrix result(n, m); // создаём матрицу для результата

    // делим каждый элемент матрицы на скаляр и записываем его в результирующую матрицу
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            result.values[i][j] = values[i][j] / scalar;

    return result; // возвращаем полученную матрицу
}

// деструктор, освобождение памяти
Matrix::~Matrix() {
    // освобождаем память из под столбцов
    for (int i = 0; i < n; i++)
        delete[] values[i];

    delete[] values; // освобождаем память из-под строк
}
