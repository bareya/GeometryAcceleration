//
// MIT License
// 
// Copyright (c) 2019 Piotr Barejko
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef VECTOR3_H
#define VECTOR3_H

#include "Types.h"

class Vector3
{
public:
    explicit Vector3(Real v = 0.0_r)
        : xyz{ v, v, v }
    {}

    Vector3(Real x, Real y, Real z)
        : xyz{ x, y, z }
    {}

    constexpr Vector3(const Vector3 &) = default;
    Vector3(Vector3 &&) = default;

    Vector3 & operator=(const Vector3 &) = default;
    Vector3 & operator=(Vector3 &&) = default;

    const Real& x() const { return xyz[0]; }
    const Real& y() const { return xyz[1]; }
    const Real& z() const { return xyz[2]; }

    Real& x() { return xyz[0]; }
    Real& y() { return xyz[1]; }
    Real& z() { return xyz[2]; }

    const Real& operator[](Index index) const { return xyz[index]; }
    Real& operator[](Index index) { return xyz[index]; }

    // Real specialization
    Vector3 operator+(Real r) const { return { x() + r, y() + r, z() + r }; }
    Vector3 operator-(Real r) const { return { x() - r, y() - r, z() - r }; }
    Vector3 operator*(Real r) const { return { x() * r, y() * r, z() * r }; }
    Vector3 operator/(Real r) const { return { x() / r, y() / r, z() / r }; }

    // Vector3 specialization
    Vector3 operator+(const Vector3 & r) const { return { x() + r.x(), y() + r.y(), z() + r.z() }; }
    Vector3 operator-(const Vector3 & r) const { return { x() - r.x(), y() - r.y(), z() - r.z() }; }
    Vector3 operator*(const Vector3 & r) const { return { x() * r.x(), y() * r.y(), z() * r.z() }; }
    Vector3 operator/(const Vector3 & r) const { return { x() / r.x(), y() / r.y(), z() / r.z() }; }

    Vector3 & operator+=(Real r) { x() += r; y() += r; z() += r; return *this; }
    Vector3 & operator-=(Real r) { x() -= r; y() -= r; z() -= r; return *this; }
    Vector3 & operator*=(Real r) { x() *= r; y() *= r; z() *= r; return *this; }
    Vector3 & operator/=(Real r) { x() /= r; y() /= r; z() /= r; return *this; }

    Vector3 & operator+=(const Vector3 & r) { x() += r.x(); y() += r.y(); z() += r.z(); return *this; }
    Vector3 & operator-=(const Vector3 & r) { x() -= r.x(); y() -= r.y(); z() -= r.z(); return *this; }
    Vector3 & operator*=(const Vector3 & r) { x() *= r.x(); y() *= r.y(); z() *= r.z(); return *this; }
    Vector3 & operator/=(const Vector3 & r) { x() /= r.x(); y() /= r.y(); z() /= r.z(); return *this; }

    Vector3 operator-() const { return { -x(), -y(), -z() }; }

private:
    Real xyz[3];
};

using Vector3Array = std::vector<Vector3>;

#endif // VECTOR3_H
