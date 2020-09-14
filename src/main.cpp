#include <iostream>
#include "../inc/matrix.h"

int main(){
    Matrix matrix1;
    Matrix matrix2;
    Matrix transposedMatrix1;
    Matrix addingResult;

    // Load matrices from a given files.
    matrix1.Load("/.../matrix_a.txt");
    matrix2.Load("/.../matrix_b.txt");

    std::cout << matrix1 << std::endl;
    std:: cout << matrix2 << std::endl;

    transposedMatrix1 = matrix1.Transpose();
    std::cout << transposedMatrix1 << std::endl;

    addingResult = matrix1 + matrix2;
    std::cout << addingResult << std::endl;

}
