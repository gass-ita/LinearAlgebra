#pragma once

#include <iostream>
#include "Vector.hpp"

template <int N, int M>
class Matrix
{
private:
    double m_matrix[N][M];

public:
    Matrix();
    ~Matrix() = default;
    Matrix(double matrix[][M]);
    // initialization with list of elements
    Matrix(std::initializer_list<std::initializer_list<double>> list);
    // get using [row][column] operator
    double *operator[](int index);
    Matrix<M, N> transpose();
    int getRows() const { return N; }
    int getColumns() const { return M; }

    Matrix<N, M> operator*(double scalar);
    Matrix<N, M> operator+(Matrix<N, M> &other);
    Matrix<N, M> operator-(Matrix<N, M> &other);
    template <int P>
    Matrix<N, P> operator*(Matrix<M, P> &other);
    // vector multiplication
    Vector<N> operator*(Vector<M> &vector);
    // Print
    template <int Rows, int Cols>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<Rows, Cols> &m);
};

template <int N, int M>
inline Matrix<N, M>::Matrix()
{
    memset(m_matrix, 0, sizeof(m_matrix));
}

template <int N, int M>
inline Matrix<N, M>::Matrix(double matrix[][M])
{
    memcpy(m_matrix, matrix, sizeof(m_matrix));
}

template <int N, int M>
inline Matrix<N, M>::Matrix(std::initializer_list<std::initializer_list<double>> list)
{
    int i = 0;
    for (auto row : list)
    {
        int j = 0;
        for (double element : row)
        {
            m_matrix[i][j] = element;
            j++;
        }
        i++;
    }
}

template <int N, int M>
inline double *Matrix<N, M>::operator[](int index)
{
    return m_matrix[index];
}

template <int N, int M>
inline Matrix<M, N> Matrix<N, M>::transpose()
{
    Matrix<M, N> result;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            result[j][i] = m_matrix[i][j];
        }
    }
    return result;
}

template <int N, int M>
inline Matrix<N, M> Matrix<N, M>::operator*(double scalar)
{
    Matrix<N, M> result;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            result[i][j] = m_matrix[i][j] * scalar;
        }
    }
    return result;
}

template <int N, int M>
inline Matrix<N, M> Matrix<N, M>::operator+(Matrix<N, M> &other)
{
    Matrix<N, M> result;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            result[i][j] = m_matrix[i][j] + other[i][j];
        }
    }
    return result;
}

template <int N, int M>
inline Matrix<N, M> Matrix<N, M>::operator-(Matrix<N, M> &other)
{
    Matrix<N, M> result;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            result[i][j] = m_matrix[i][j] - other[i][j];
        }
    }
    return result;
}

template <int N, int M>
inline Vector<N> Matrix<N, M>::operator*(Vector<M> &vector)
{
    Vector<N> result;
    for (int i = 0; i < N; i++)
    {
        result[i] = 0;
        for (int j = 0; j < M; j++)
        {
            result[i] += m_matrix[i][j] * vector[j];
        }
    }
    return result;
}

template <int N, int M>
template <int P>
inline Matrix<N, P> Matrix<N, M>::operator*(Matrix<M, P> &other)
{
    Matrix<N, P> result;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < M; k++)
            {
                result[i][j] += m_matrix[i][k] * other[k][j];
            }
        }
    }
    return result;
}

template <int Rows, int Cols>
std::ostream &operator<<(std::ostream &os, const Matrix<Rows, Cols> &m)
{
    for (int i = 0; i < Rows; i++)
    {
        os << "[";
        for (int j = 0; j < Cols - 1; j++)
        {
            os << m.m_matrix[i][j] << ", ";
        }
        os << m.m_matrix[i][Cols - 1] << "]" << std::endl;
    }
    return os;
}
