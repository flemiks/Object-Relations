#include "Matrix.h"

int main() {
    Matrix<int> mat1(2, 2);
    Matrix<int> mat2(3, 3);
    mat1.addRandomValues();
    mat2.addRandomValues();
    Matrix<int> mat3 = mat2 + mat1;
    mat3.printMatrix();
    cout << endl;
    Matrix<char> mat4(3, 3);
    mat4.addRandomValues();
    mat4.printMatrix();
    Matrix<float> mat5(5, 3);
    mat5.addRandomValues();
    mat5.printMatrix();
    return 0;
}