#pragma once

#include "Vector3.hpp"

Vector3::Vector3(double x, double y, double z)
{
    this->m_x = x;
    this->m_y = y;
    this->m_z = z;
}

double Vector3::dot(Vector3 &v1, Vector3 &v2)
{
    return (v1.m_x * v2.m_x) + (v1.m_y * v2.m_y) + (v1.m_z * v2.m_z);
}

/* // row by column multiplication
Vector3 Vector3::matrixMultiplication(double matrix[3][3])
{
    double x = this->m_x * matrix[0][0] + this->m_y * matrix[0][1] + this->m_z * matrix[0][2];
    double y = this->m_x * matrix[1][0] + this->m_y * matrix[1][1] + this->m_z * matrix[1][2];
    double z = this->m_x * matrix[2][0] + this->m_y * matrix[2][1] + this->m_z * matrix[2][2];
    return Vector3(x, y, z);
} */

Vector3 Vector3::operator+(Vector3 &other)
{
    return Vector3(this->m_x + other.m_x, this->m_y + other.m_y, this->m_z + other.m_z);
}

Vector3 Vector3::operator-(Vector3 &other)
{
    return Vector3(this->m_x - other.m_x, this->m_y - other.m_y, this->m_z - other.m_z);
}

bool Vector3::operator==(Vector3 &other)
{
    return this->m_x == other.m_x && this->m_y == other.m_y && this->m_y == other.m_y;
}

std::ostream &operator<<(std::ostream &os, const Vector3 &v)
{
    os << "(" << v.m_x << ", " << v.m_y << ", " << v.m_z << ")";
    return os;
}
