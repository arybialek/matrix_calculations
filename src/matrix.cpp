/*
 * Definition of constructors, methods and operator overloading
 * that are associated with a Matrix class.
 */

#include <iostream>
#include <fstream>
#include "../inc/matrix.h"

/* ##################################################################
 * Constructors
 * ##################################################################
 */
Matrix::Matrix() {}

Matrix::Matrix(unsigned num_rows, unsigned num_cols){
    for(unsigned idx1 = 0; idx1 < num_rows; ++idx1){
        std::vector<double> row; // empty row to store the data

        for(unsigned idx2 = 0; idx2 < num_cols; ++idx2)
            row.push_back(0.0); // append 0.0 at the end of a row

        matrix.push_back(row); // add a new row to the matrix
    }
}

/* ################################################################################
 * Methods
 * ################################################################################
 */

// Load matrix from file.
void Matrix::Load(const std::string& pathToFile){
    std::ifstream file;
    file.open(pathToFile);

    if(!file){
        // If file does not exist or if there is an error with opening the file.
        std::cerr << "Error when opening matrix file.\n";
        return;
    }

    file >> row >> col; // Read matrix dimensions.
    if(row < 1 || col < 1){
        std::cerr << "Matrix sizes are out of bounds.\n";
        return;
    }

    // Allocate a matrix with a proper size.
    this->matrix.resize(row);
    for(auto& matrixRow : this->matrix)
        matrixRow.resize(col);

    // Read the input file.
    for(auto& matrixRow : this->matrix)
        for(auto& matrixCol : matrixRow)
            file >> matrixCol;

}

// Transpose given matrix.
Matrix Matrix::Transpose() const{
    Matrix transpose_result(this->matrix.size(), this->matrix[0].size());

    for(unsigned row = 0; row < this->matrix.size(); ++row)
        for(unsigned col = 0; col < this->matrix[0].size(); ++col)
            transpose_result(row, col) = matrix[col][row];
    return transpose_result;
}


/* ##########################################################################
 * Operator overloading
 * ##########################################################################
 */

// Overload << operator to print the matrix.
std::ostream& operator << (std::ostream &str, const Matrix& matrix){
    for(unsigned idx1 = 0; idx1 < matrix.matrix.size(); ++idx1)
        for(unsigned idx2 = 0; idx2 < matrix.matrix[idx1].size(); ++idx2)
        {
            if(idx2 == (matrix.matrix[idx1].size() - 1))
                str << matrix.matrix[idx1][idx2] << std::endl;
            else
                str << matrix.matrix[idx1][idx2] << " ";
        }
    return str;
}

// Overload + operator.
Matrix operator + (const Matrix& matrix1, const Matrix& matrix2)
{
    if(matrix1.matrix.size() != matrix2.matrix.size())
        throw "Incompatible matrices dimensions - adding impossible.";
    if(matrix1.matrix[0].size() != matrix2.matrix[0].size())
        throw "Incompatible matrices dimensions - adding impossible.";

    Matrix additionResult(matrix1.matrix.size(), matrix1.matrix[0].size());

    for(unsigned idx1 = 0; idx1 < matrix1.matrix.size(); ++idx1)
        for(unsigned idx2 = 0; idx2 < matrix1.matrix[0].size(); ++idx2)
            additionResult(idx1, idx2) = matrix1.matrix[idx1][idx2] + matrix2.matrix[idx1][idx2];

    return additionResult;
}