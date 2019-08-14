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

#ifndef MESH_H
#define MESH_H

#include <Core/AABBox.h>

#include <type_traits>
#include <memory>

class Face;

class Mesh
{
public:
    Mesh() = default;

    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    Mesh& operator=(Mesh&&) = delete;

    ~Mesh();

    //
    // Points
    //
    Index NumPoints() const { return positions_.size(); }

    const Vector3 & GetPosition(Index i) const { return positions_[i]; }
    Vector3 & GetPosition(Index i) { return positions_[i]; }

    Index AppendPoint(Real x, Real y, Real z)
    {
        positions_.emplace_back(x, y, z);
        return positions_.size() - 1;
    }

    //
    // Faces
    //
    Index NumFaces() const { return faces_.size(); }

    Face* GetFace(Index i) { return faces_[i].get(); }
    const Face* GetFace(Index i) const { return faces_[i].get(); }

    template<typename T, typename... Args>
    T* AppendFace(Args&& ... args)
    {
        static_assert(std::is_base_of<Face, T>::value, "AppendFace: T does not derive from Face interface.");

        std::unique_ptr<T> new_face{new T{*this, std::forward<Args>(args)...}};
        T* ptr = new_face.get();

        faces_.push_back(std::move(new_face));
        return ptr;
    }

    void Clear()
    {
        positions_.clear();
        
        faces_.clear();
        offsets_.clear();
        counts_.clear();
        vertices_.clear();
        num_vertices_ = 0;
    }

    friend class Face;

private:
    Index AppendFaceVertices(IndexArray vertices)
    {
        Index offset = vertices_.size();

        auto count = vertices.size();
        num_vertices_ += count;
        vertices_.insert(vertices_.end(), vertices.begin(), vertices.end());
        counts_.push_back(count);
        offsets_.push_back(offset);
        return offset;
    }

    // point attributes
    Vector3Array positions_;

    // face information storage
    Index num_vertices_{};      // total number of vertices
    IndexArray vertices_;       // point indices
    IndexArray counts_;         // vertex count per face
    IndexArray offsets_;        // global offset per face
    std::vector<std::unique_ptr<Face>> faces_;
};

#endif // MESH_H
