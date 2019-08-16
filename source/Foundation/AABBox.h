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

#ifndef AABBOX_H
#define AABBOX_H

#include "Vector3.h"

class AABBox
{
public:
    explicit AABBox(Vector3 mn = Vector3{REAL_INFINITY},
                    Vector3 mx = Vector3{-REAL_INFINITY})
        : min_{mn}, max_{mx}
    {}

    AABBox(const AABBox&) = default;
    AABBox(AABBox&&) = default;

    AABBox& operator=(const AABBox&) = default;
    AABBox& operator=(AABBox&&) = default;

    const Vector3 & MinPoint() const { return min_; }
    const Vector3 & MaxPoint() const { return max_; }

    Vector3 Size() const { return max_ - min_; }
    Vector3 Center() const { return min_ + (Size() * 0.5_r); }
    //Vector3 Closest(const Vector3 & p) const { return ::Clamp(p, min_, max_); }

    Index MaxExtent() const;

private:
    Vector3 min_;
    Vector3 max_;
};

inline Index AABBox::MaxExtent() const
{
    const auto size = Size();
    if (size.x() > size.y() && size.x() > size.z()) return 0;
    else if (size.y() > size.z()) return 1;
    else return 2;
}

#endif // AABBOX_H
