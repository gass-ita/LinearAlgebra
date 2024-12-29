#include "Vector3.hpp"

class Matrix
{
private:
    double m_matrix[3][3];

public:
    Matrix();
    ~Matrix() = default;
    Matrix(double matrix[][3]);
    // get using [row][column] operator
    double *operator[](int index);
    Matrix operator*(Matrix &other);
    int getRows();
    int getColumns();
    Matrix operator*(double scalar);
    Vector3 operator*(Vector3 &vector);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
};
