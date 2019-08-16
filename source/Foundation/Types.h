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

#ifndef TYPES_H
#define TYPES_H

#include <limits>
#include <vector>

using Real = float;
using Index = unsigned long long;

constexpr Real operator"" _r(long double v) { return static_cast<Real>(v); }
constexpr Real operator"" _r(unsigned long long v) { return static_cast<Real>(v); }
constexpr Index operator"" _i(unsigned long long v) { return static_cast<Index>(v); }

constexpr Real REAL_INFINITY = std::numeric_limits<Real>::infinity();
constexpr Index INDEX_INVALID = static_cast<Index>(-1);

using IndexArray = std::vector<Index>;
using RealArray = std::vector<Real>;

#endif // TYPES_H
