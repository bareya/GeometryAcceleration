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

#ifndef MATH_H
#define MATH_H

#include "Vector3.h"
#include "AABBox.h"

#include <algorithm>

constexpr Real Clamp(Real val, Real mn, Real mx)
{
    return val < mn ? mn : val > mx ? mx : val;
}

inline Vector3 Min(const Vector3 & l, const Vector3 & r)
{
    return {std::min(l.x(), r.x()),
            std::min(l.y(), r.y()),
            std::min(l.z(), r.z())};
}

inline Vector3 Max(const Vector3 & l, const Vector3 & r)
{
    return {std::max(l.x(), r.x()),
            std::max(l.y(), r.y()),
            std::max(l.z(), r.z())};
}

inline Vector3 Clamp(const Vector3& v, const Vector3& mn, const Vector3& mx)
{
    return {::Clamp(v.x(), mn.x(), mx.x()),
            ::Clamp(v.y(), mn.y(), mx.y()),
            ::Clamp(v.z(), mn.z(), mx.z())};
}

inline AABBox Union(const AABBox& l, const Vector3& r)
{
    return AABBox{::Min(l.MinPoint(), r),
                  ::Max(l.MaxPoint(), r)};
}

inline AABBox Union(const AABBox& l, const AABBox& r)
{
    return AABBox{::Min(l.MinPoint(), r.MinPoint()),
                  ::Max(l.MaxPoint(), r.MaxPoint())};
}

#endif // MATH_H
