#include "Vector3.hpp"

class Matrix3
{
private:
    double m_matrix[3][3];

public:
    Matrix3();
    ~Matrix3() = default;
    Matrix3(double matrix[][3]);
    // get using [row][column] operator
    double *operator[](int index);
    Matrix3 operator*(Matrix3 &other);
    int getRows();
    int getColumns();
    Matrix3 operator*(double scalar);
    Vector3 operator*(Vector3 &vector);
    friend std::ostream &operator<<(std::ostream &os, const Matrix3 &m);
};
