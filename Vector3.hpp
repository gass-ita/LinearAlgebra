#pragma once
#include <ostream>

class Vector3
{
private:
public:
    double m_x = 0, m_y = 0, m_z = 0;
    Vector3(double x, double y, double z);
    Vector3() = default;
    ~Vector3() = default;
    double dot(Vector3 &v1, Vector3 &v2);
    // row by column multiplication
    /* Vector3 matrixMultiplication(double matrix[3][3]); */
    Vector3 operator+(Vector3 &other);
    Vector3 operator-(Vector3 &other);
    bool operator==(Vector3 &other);
    friend std::ostream &operator<<(std::ostream &os, const Vector3 &v);
};