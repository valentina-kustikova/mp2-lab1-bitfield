#include "matrix.hpp"

#include <time.h>
#include <stdlib.h>

using namespace std;

Matrix::Matrix(int _kRows, int _kCols) : kRows(_kRows), kCols(_kCols)
{
    values = new uchar*[kRows];
    for (int i = 0; i < kRows; i++)
    {
        values[i] = new uchar[kCols];
    }
}

Matrix::Matrix(const Matrix& m)
{
    kRows = m.kRows;
    kCols = m.kCols;

    values = new uchar*[kRows];

    for (int i = 0; i < kRows; i++)
    {
        values[i] = new uchar[kCols];
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = m[i][j];
        }
    }
}

void Matrix::Zeros()
{
    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = 0;
        }
    }
}

void Matrix::Ones()
{
    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = 1;
        }
    }
}

void Matrix::Random(int seed)
{
    srand(seed);

    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            values[i][j] = (uchar) (rand() % 256);
        }
    }
}

Matrix::~Matrix()
{
    if (values)
    {
        for (int i = 0; i < kRows; i++)
        {
            if (values[i])
                delete [] values[i];
        }
        delete [] values;
    }
}

bool Matrix::operator==(const Matrix& m) const
{
    if (kRows != m.kRows || kCols != m.kCols)
    {
        return false;
    }

    for (int i = 0; i < kRows; i++)
    {
        for (int j = 0; j < kCols; j++)
        {
            if (values[i][j] != m[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.kRows; i++)
    {
        for (int j = 0; j < m.kCols; j++)
        {
            os << (int)(m.values[i][j]) << '\t';
        }
        os << endl;
    }

    return os;
}
