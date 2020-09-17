/*
 * Definition of constructors, methods and operator overloading
 * that are associated with a Matrix class.
 */

#include <iostream>
#include <cmath>
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

Matrix::Matrix(const Matrix& original)
{
    for(unsigned idx1 = 0; idx1 < original.matrix.size(); ++idx1)
    {
        std::vector<double> tmpRow; // empty row for data storage

        for(unsigned idx2 = 0; idx2 < original.matrix[0].size(); ++idx2)
            tmpRow.push_back(original(idx1,idx2));

        matrix.push_back(tmpRow); // add new row to the matrix
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
        throw std::invalid_argument("Error when opening matrix file.\n");
    }

    file >> row >> col; // Read matrix dimensions.
    if(row < 1 || col < 1){
        throw std::invalid_argument("Matrix sizes are out of bounds.\n");
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

// Sum of elements.
double Matrix::SumOfElements() const{
    double sumOfElements = 0;

    for(unsigned row = 0; row < this->matrix.size(); ++row)
        for(unsigned  col = 0; col < this->matrix[0].size(); ++col)
            sumOfElements += matrix[row][col];

    return sumOfElements;
}

// Determinant.
double Matrix::Determinant() const{

    if(this->matrix.size() != this->matrix[0].size())
        throw std::invalid_argument("Invalid matrix shape to compute a determinant for a given matrix.");

    if(this->matrix.size() == 1 and this->matrix[0].size() == 1)
        return matrix[0][0];

    if(this->matrix.size() == 2 and this->matrix[0].size() == 2)
        return (this->matrix[0][0] * this->matrix[1][1]) - (this->matrix[1][0] * this->matrix[0][1]);

    // Iterate over every element of the first row.
    int sign = 1;
    double result = 0;
    for(unsigned element_idx = 0; element_idx < this->matrix[0].size(); ++element_idx){
        Matrix subMatrix;
        for(unsigned row_idx = 1; row_idx < this->matrix.size(); ++row_idx){
            std::vector<double> tmpRow;
            for(unsigned col_idx = 0; col_idx < this->matrix[0].size(); ++col_idx){
                if(col_idx != element_idx)
                    tmpRow.push_back(this->matrix[row_idx][col_idx]);
            }
            subMatrix.matrix.push_back(tmpRow);
        }

        double det = subMatrix.Determinant();
        result += this->matrix[0][element_idx] * sign * det;
        sign *= -1;
    }
    return result;
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
Matrix operator + (const Matrix& matrix1, const Matrix& matrix2){
    if(matrix1.matrix.size() != matrix2.matrix.size())
        throw std::invalid_argument("Incompatible matrices dimensions - adding impossible.");
    if(matrix1.matrix[0].size() != matrix2.matrix[0].size())
        throw std::invalid_argument("Incompatible matrices dimensions - adding impossible.");

    Matrix additionResult(matrix1.matrix.size(), matrix1.matrix[0].size());

    for(unsigned idx1 = 0; idx1 < matrix1.matrix.size(); ++idx1)
        for(unsigned idx2 = 0; idx2 < matrix1.matrix[0].size(); ++idx2)
            additionResult(idx1, idx2) = matrix1.matrix[idx1][idx2] + matrix2.matrix[idx1][idx2];

    return additionResult;
}

// Overload * operator to do matrices multiplication.
Matrix operator * (const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.matrix.size() != matrix2.matrix[0].size())
        throw std::invalid_argument("Incompatible matrices dimensions - multiplication impossible.");

    Matrix multiplicationResult(matrix1.matrix.size(), matrix2.matrix[0].size());

    for(unsigned idx0 = 0; idx0 < matrix2.matrix[0].size(); ++idx0){
        for(unsigned idx1 = 0; idx1 < matrix1.matrix.size(); ++idx1){
            double helperSum = 0;

            for(unsigned idx2 = 0; idx2 < matrix1.matrix[0].size(); ++idx2)
                helperSum += matrix1.matrix[idx1][idx2] * matrix2.matrix[idx2][idx0];

            multiplicationResult(idx1, idx0) = helperSum;
        }
    }
    return multiplicationResult;
}
