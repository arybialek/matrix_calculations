#include <iostream>
#include "../inc/matrix.h"

int main(){
    Matrix matrix1;
    Matrix matrix2;
    Matrix transposedMatrix1;
    Matrix addingResult;
    Matrix multiplicationResult;
    double sumOfElements;
    double determinant;

    // Load matrices from a given files.
    matrix1.Load("/home/anita/Pulpit/matrix_calculations/matrix_a.txt");
    matrix2.Load("/home/anita/Pulpit/matrix_calculations/matrix_b.txt");

    std::cout << matrix1 << std::endl;
    std:: cout << matrix2 << std::endl;

    transposedMatrix1 = matrix1.Transpose();
    std::cout << transposedMatrix1 << std::endl;

    addingResult = matrix1 + matrix2;
    std::cout << addingResult << std::endl;

    multiplicationResult = matrix1 * matrix2;
    std::cout << multiplicationResult << std::endl;

    sumOfElements = matrix1.SumOfElements();
    std::cout << sumOfElements << std::endl;

    determinant = matrix1.Determinant();
    std::cout << determinant << std::endl;

}
