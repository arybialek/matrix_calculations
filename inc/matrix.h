#ifndef MATRIX_CALCULATIONS_MATRIX_H
#define MATRIX_CALCULATIONS_MATRIX_H

/*
 * Matrix class.
 *
 * This file contains a Matrix class that allows you to store 2D matrices.
 */

#include <iostream>
#include <vector>

class Matrix{
    // Give access to private members.
    friend std::ostream& operator << (std::ostream &str, const Matrix& matrix);
    friend Matrix operator + (const Matrix& matrix1, const Matrix& matrix2);

    public:
        Matrix();
        Matrix(unsigned num_rows, unsigned num_cols);
        Matrix Transpose() const;
        void Load(const std::string& pathToFile);

        // Definition of the () operator overloading - for convenient access to elements.
        const double& operator () (unsigned row, unsigned col) const{
            return matrix[row][col];}
        double& operator () (unsigned row, unsigned col) {
            return matrix[row][col];}
    private:
        unsigned row, col;
        std::vector<std::vector<double>> matrix; // Prepare empty 2D array.
};

#endif //MATRIX_CALCULATIONS_MATRIX_H
