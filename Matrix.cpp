#include "Matrix.hpp"

#include <cstring>

Matrix::Matrix()
{
    memset(m_matrix, 0, sizeof(m_matrix));
}

Matrix::Matrix(double matrix[][3])
{
    memcpy(m_matrix, matrix, sizeof(m_matrix));
}

double *Matrix::operator[](int index)
{
    return m_matrix[index];
}

Matrix Matrix::operator*(Matrix &other)
{
    Matrix result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++)
            {
                result[i][j] += m_matrix[i][k] * other[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar)
{
    Matrix result;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = m_matrix[i][j] * scalar;
        }
    }
    return result;
}

Vector3 Matrix::operator*(Vector3 &vector)
{
    double x = vector.m_x * m_matrix[0][0] + vector.m_y * m_matrix[0][1] + vector.m_z * m_matrix[0][2];
    double y = vector.m_x * m_matrix[1][0] + vector.m_y * m_matrix[1][1] + vector.m_z * m_matrix[1][2];
    double z = vector.m_x * m_matrix[2][0] + vector.m_y * m_matrix[2][1] + vector.m_z * m_matrix[2][2];
    return Vector3(x, y, z);
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    os << "Matrix: " << std::endl;
    for (int i = 0; i < 3; i++)
    {
        os << "[ ";
        for (int j = 0; j < 3; j++)
        {
            os << m.m_matrix[i][j] << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}
