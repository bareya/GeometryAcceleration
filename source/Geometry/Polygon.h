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

#ifndef POLYGON_H
#define POLYGON_H

#include "Face.h"

#include <Foundation/Math.h>

class Polygon final : public Face
{
public:
    Polygon(Mesh& mesh, std::vector<Index>&& vertices)
        : Face(mesh, std::move(vertices))
    {
    }

    Vector3 Centroid() const final
    {
        const Index num_vertices = NumVertices();
        Vector3 centroid;
        for (Index i{}; i < num_vertices; ++i)
        {
            const Vector3 & pos = GetPosition(i);
            centroid += pos;
        }
        return centroid / static_cast<Real>(num_vertices);
    }

    AABBox Bounds() const final
    {
        AABBox bounds;
        for (Index i{}; i < NumVertices(); ++i)
        {
            bounds = ::Union(bounds, GetPosition(i));
        }
        return bounds;
    }
};

#endif // POLYGON_H
