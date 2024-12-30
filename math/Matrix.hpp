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

    double determinant();
    Matrix<N, M> adjugate();
    Matrix<M, N> inverse();

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

template <int N, int M>
double Matrix<N, M>::determinant()
{
    static_assert(N == M, "Determinant can only be calculated for square matrices");

    if constexpr (N == 1)
    {
        return m_matrix[0][0];
    }
    else if constexpr (N == 2)
    {
        // Base case for 2x2 matrix
        return m_matrix[0][0] * m_matrix[1][1] - m_matrix[0][1] * m_matrix[1][0];
    }
    else
    {
        double det = 0.0;
        for (int j = 0; j < M; j++)
        {
            if constexpr (N > 1 && M > 1) // Ensure N and M are greater than 1
            {
                Matrix<N - 1, M - 1> subMatrix;
                for (int row = 1; row < N; row++)
                {
                    int subCol = 0;
                    for (int col = 0; col < M; col++)
                    {
                        if (col == j)
                            continue;
                        subMatrix[row - 1][subCol] = m_matrix[row][col];
                        subCol++;
                    }
                }
                det += (j % 2 == 0 ? 1 : -1) * m_matrix[0][j] * subMatrix.determinant();
            }
        }
        return det;
    }
}

template <int N, int M>
Matrix<N, M> Matrix<N, M>::adjugate()
{
    static_assert(N == M, "Adjugate can only be calculated for square matrices");

    Matrix<N, M> adj;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            // Compute the cofactor for element (i, j)
            Matrix<N - 1, M - 1> subMatrix;

            int subRow = 0;
            for (int row = 0; row < N; row++)
            {
                if (row == i)
                    continue;

                int subCol = 0;
                for (int col = 0; col < M; col++)
                {
                    if (col == j)
                        continue;

                    subMatrix[subRow][subCol] = m_matrix[row][col];
                    subCol++;
                }
                subRow++;
            }

            // Element (i, j) of adjugate is the determinant of the submatrix
            adj[j][i] = (i + j) % 2 == 0 ? subMatrix.determinant() : -subMatrix.determinant();
        }
    }

    return adj;
}

template <int N, int M>
Matrix<M, N> Matrix<N, M>::inverse()
{
    static_assert(N == M, "Inverse can only be calculated for square matrices");

    double det = determinant();
    if (det == 0)
    {
        throw std::runtime_error("Matrix is singular and cannot be inverted");
    }

    return adjugate() * (1 / det);
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
