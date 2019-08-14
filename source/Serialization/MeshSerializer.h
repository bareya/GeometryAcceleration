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

#ifndef MESH_SERIALIZER_H
#define MESH_SERIALIZER_H

#include <iosfwd>
#include <memory>

class Mesh;

///
/// \brief MeshSerializer interface
///
class MeshSerializer
{
public:
    MeshSerializer(const MeshSerializer&) = delete;
    MeshSerializer(MeshSerializer&&) = delete;

    MeshSerializer& operator=(const MeshSerializer&) = delete;
    MeshSerializer& operator=(MeshSerializer&&) = delete;

    virtual ~MeshSerializer();

    virtual bool Save(std::ostream& os, const std::shared_ptr<Mesh>& mesh) = 0;
    virtual bool Load(std::istream& is, std::shared_ptr<Mesh>& mesh) = 0;

protected:
    MeshSerializer() = default;
};

#endif // MESH_SERIALIZER_H
