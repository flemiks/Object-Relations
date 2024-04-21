#pragma once

#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <random>
#include <limits>

using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int cols;
    T** matrix;

    void allocateMatrix() {
        matrix = new T * [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new T[cols]();
        }
    }

public:
    Matrix(int rows = 1, int cols = 1) : rows(rows), cols(cols) {
        if (rows <= 0 || cols <= 0) {
            throw invalid_argument("Rows and columns must be greater than 0.");
        }
        allocateMatrix();
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void enterValues() {
        T value;
        cin.exceptions(ios::failbit | ios::badbit);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                while (true) {
                    cout << "Enter value for [" << i << "][" << j << "]: ";
                    try {
                        cin >> value;
                        matrix[i][j] = value;
                        break;
                    }
                    catch (ios_base::failure& e) {
                        cout << "Enter error: " << e.what() << ". Repeat again." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
            }
        }
    }

    void addRandomValues() {
        random_device rd;
        mt19937 gen(rd());

        if constexpr (is_integral<T>::value && !is_same<T, char>::value) {
            uniform_int_distribution<int> dis(1, 100);  
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = static_cast<T>(dis(gen));
                }
            }
        }
        else if constexpr (is_same<T, char>::value) {
            uniform_int_distribution<int> dis(32, 126);  
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = static_cast<T>(dis(gen));
                }
            }
        }
        else if constexpr (is_floating_point<T>::value) {
            uniform_real_distribution<T> dis(0.0, 1.0);  
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    matrix[i][j] = dis(gen);
                }
            }
        }
    }

    void printMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " , ";
            }
            cout << endl;
        }
    }

    T findMax() {
        T max = matrix[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                max = (max > matrix[i][j]) ? max : matrix[i][j];
            }
        }
        return max;
    }

    T findMin() {
        T min = matrix[0][0];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                min = (min < matrix[i][j]) ? min : matrix[i][j];
            }
        }
        return min;
    }

    T& operator()(int row, int col) {
        if (row >= rows || col >= cols) {
            throw out_of_range("Index out of range.");
        }
        return matrix[row][col];
    }

    const T& operator()(int row, int col) const {
        if (row >= rows || col >= cols) {
            throw out_of_range("Index out of range.");
        }
        return matrix[row][col];
    }

    friend Matrix operator+(const Matrix<T>& m1, const Matrix<T>& m2) {
        static_assert(is_arithmetic<T>::value && !is_same<T, char>::value, "Operator + is only valid for numeric types excluding char and string.");
        int maxRows = max(m1.rows, m2.rows);
        int maxCols = max(m1.cols, m2.cols);
        Matrix<T> result(maxRows, maxCols);
        for (int i = 0; i < maxRows; ++i) {
            for (int j = 0; j < maxCols; ++j) {
                T val1 = (i < m1.rows && j < m1.cols) ? m1(i, j) : 0;
                T val2 = (i < m2.rows && j < m2.cols) ? m2(i, j) : 0;
                result(i, j) = val1 + val2;
            }
        }
        return result;
    }
    friend Matrix operator-(const Matrix<T>& m1, const Matrix<T>& m2) {
        static_assert(is_arithmetic<T>::value && !is_same<T, char>::value, "Operator + is only valid for numeric types excluding char and string.");
        int maxRows = max(m1.rows, m2.rows);
        int maxCols = max(m1.cols, m2.cols);
        Matrix<T> result(maxRows, maxCols);
        for (int i = 0; i < maxRows; ++i) {
            for (int j = 0; j < maxCols; ++j) {
                T val1 = (i < m1.rows && j < m1.cols) ? m1(i, j) : 0;
                T val2 = (i < m2.rows && j < m2.cols) ? m2(i, j) : 0;
                result(i, j) = val1 - val2;  
            }
        }
        return result;
    }
    friend Matrix operator/(const Matrix<T>& m1, const Matrix<T>& m2) {
        static_assert(is_arithmetic<T>::value && !is_same<T, char>::value, "Operator + is only valid for numeric types excluding char and string.");
        int maxRows = max(m1.rows, m2.rows);
        int maxCols = max(m1.cols, m2.cols);
        Matrix<T> result(maxRows, maxCols);
        for (int i = 0; i < maxRows; ++i) {
            for (int j = 0; j < maxCols; ++j) {
                T val1 = (i < m1.rows && j < m1.cols) ? m1(i, j) : 0;
                T val2 = (i < m2.rows && j < m2.cols) ? m2(i, j) : 0;
                if (val1 == 0) {
                    result(i, j) = val2;
                }
                else if (val2 == 0) {
                    result(i, j) = val1;
                }
                else {
                    result(i, j) = val1 / val2;
                }  
            }
        }
        return result;
    }
    friend Matrix operator*(const Matrix<T>& m1, const Matrix<T>& m2) {
        static_assert(is_arithmetic<T>::value && !is_same<T, char>::value, "Operator + is only valid for numeric types excluding char and string.");
        int maxRows = max(m1.rows, m2.rows);
        int maxCols = max(m1.cols, m2.cols);
        Matrix<T> result(maxRows, maxCols);
        for (int i = 0; i < maxRows; ++i) {
            for (int j = 0; j < maxCols; ++j) {
                T val1 = (i < m1.rows && j < m1.cols) ? m1(i, j) : 0;
                T val2 = (i < m2.rows && j < m2.cols) ? m2(i, j) : 0;
                result(i, j) = val1 * val2;
            }
        }
        return result;
    }
};
