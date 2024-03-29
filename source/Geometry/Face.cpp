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

#include "Face.h"
#include "Mesh.h"

Face::Face(Mesh& mesh, IndexArray&& vertices)
    : Prim()
    , mesh_(mesh)
    , index_(mesh_.NumFaces())
{
    mesh_.AppendFaceVertices(std::move(vertices));
}

const Vector3 & Face::GetPosition(Index vertex) const
{
    Index vertex_offset = mesh_.offsets_[index_];
    Index point_offset = mesh_.vertices_[vertex_offset + vertex];
    return mesh_.positions_[point_offset];
}

Vector3 & Face::GetPosition(Index vertex)
{
    Index vertex_offset = mesh_.offsets_[index_];
    Index point_offset = mesh_.vertices_[vertex_offset + vertex];
    return mesh_.positions_[point_offset];
}

Index Face::NumVertices() const
{
    return mesh_.counts_[index_];
}