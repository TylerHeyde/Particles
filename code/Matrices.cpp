#include "Matrices.h"

//Construct a matrix of the specified size.
///Initialize each element to 0.
Matrices::Matrix::Matrix(int _rows, int _cols)
{
    rows = _rows;
    cols = _cols;
    
    a.resize(rows);
    for (int i = 0; i < _rows; i++)
		a[i].resize(cols, 0.0);
}
///Add each corresponding element.
///usage:  c = a + b;
Matrices::Matrix Matrices::operator+(const Matrices::Matrix& a, const Matrices::Matrix& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        throw std::invalid_argument("Matrix sizes must match");

    Matrices::Matrix c(a.getRows(), a.getCols());
    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < a.getCols(); j++)
            c(i, j) = a(i, j) + b(i, j);
    return c;
}

///Matrix multiply.  See description.
///usage:  c = a * b;
Matrices::Matrix Matrices::operator*(const Matrices::Matrix& a, const Matrices::Matrix& b)
{
    if (a.getCols() != b.getRows())
        throw std::invalid_argument("Number of columns in the first matrix need to match the number of rows in the second matrix");
    
    Matrices::Matrix c(a.getRows(), b.getCols());
    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < b.getCols(); j++)
            for (int k = 0; k < a.getCols(); k++)
                c(i,j) += a(i,k) * b(k,j);
    return c;
}

///Matrix comparison.  See description.
///usage:  a == b
bool Matrices::operator==(const Matrices::Matrix& a, const Matrices::Matrix& b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
        return false;
    for (int i = 0; i < a.getRows(); i++)
        for (int j = 0; j < a.getCols(); j++)
            if(a(i,j) != b(i,j))
                return false;
    return true;
}

///Matrix comparison.  See description.
///usage:  a != b
bool Matrices::operator!=(const Matrices::Matrix& a, const Matrices::Matrix& b)
{
    return !(a == b);
}

///Output matrix.
///Separate columns by ' ' and rows by '\n'
ostream& Matrices::operator<<(ostream& os, const Matrices::Matrix& a)
{
    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            os << a(i,j) << " ";
        }
        os << "\n";
    }
    return os;
}

Matrices::ScalingMatrix::ScalingMatrix(double scale) : Matrices::Matrix(2,2)
{
    a.at(0).at(0) = scale;
    a.at(1).at(1) = scale;
}

Matrices::RotationMatrix::RotationMatrix(double theta) : Matrices::Matrix(2,2)
{
    a.at(0).at(0) = cos(theta);
    a.at(0).at(1) = -sin(theta);
    a.at(1).at(0) = sin(theta);
    a.at(1).at(1) = cos(theta);
}

Matrices::TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrices::Matrix(2,nCols)
{
    for (int j = 0; j < nCols; j++)
    {
        a.at(0).at(j) = xShift;
        a.at(1).at(j) = yShift;
    }
}
