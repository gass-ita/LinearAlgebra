#pragma once
#include <iostream>

template <int N>
class Vector
{
private:
    double m_vector[N];

public:
    Vector();
    Vector(double vector[N]);
    // initialization with list of elements
    Vector(std::initializer_list<double> list);
    ~Vector() = default;
    double &operator[](int index);
    Vector<N> operator+(Vector<N> &other);
    Vector<N> operator-(Vector<N> &other);
    Vector<N> operator*(double scalar);
    double dot(Vector<N> &other);
    double magnitude();
    Vector<N> normalize();
    template <int M>
    friend std::ostream &operator<<(std::ostream &os, const Vector<M> &v);
};

template <int N>
inline Vector<N>::Vector()
{
    memset(m_vector, 0, sizeof(m_vector));
}

template <int N>
inline Vector<N>::Vector(double vector[N])
{
    memcpy(m_vector, vector, sizeof(m_vector));
}

template <int N>
inline Vector<N>::Vector(std::initializer_list<double> list)
{
    int i = 0;
    for (double element : list)
    {
        m_vector[i] = element;
        i++;
    }
}

template <int N>
inline double &Vector<N>::operator[](int index)
{
    return m_vector[index];
}

template <int N>
inline Vector<N> Vector<N>::operator+(Vector<N> &other)
{
    Vector<N> result;
    for (int i = 0; i < N; i++)
    {
        result[i] = m_vector[i] + other[i];
    }
    return result;
}

template <int N>
inline Vector<N> Vector<N>::operator-(Vector<N> &other)
{
    Vector<N> result;
    for (int i = 0; i < N; i++)
    {
        result[i] = m_vector[i] - other[i];
    }
    return result;
}

template <int N>
inline Vector<N> Vector<N>::operator*(double scalar)
{
    Vector<N> result;
    for (int i = 0; i < N; i++)
    {
        result[i] = m_vector[i] * scalar;
    }
    return result;
}

template <int N>
inline double Vector<N>::dot(Vector<N> &other)
{
    double result = 0;
    for (int i = 0; i < N; i++)
    {
        result += m_vector[i] * other[i];
    }
    return result;
}

template <int N>
inline double Vector<N>::magnitude()
{
    return sqrt(this->dot(*this));
}

template <int N>
inline Vector<N> Vector<N>::normalize()
{
    double mag = this->magnitude();
    Vector<N> result;
    for (int i = 0; i < N; i++)
    {
        result[i] = m_vector[i] / mag;
    }
    return result;
}

template <int N>
std::ostream &operator<<(std::ostream &os, const Vector<N> &v)
{
    if (N == 0)
    {
        return os;
    }
    os << "[";
    for (int i = 0; i < N - 1; i++)
    {
        os << v.m_vector[i] << ", ";
    }
    os << v.m_vector[N - 1] << "]";
    return os;
}