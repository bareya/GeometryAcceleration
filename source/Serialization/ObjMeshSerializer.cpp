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

#include "ObjMeshSerializer.h"

#include <Geometry/Mesh.h>
#include <Geometry/Face.h>
#include <Geometry/Polygon.h>
#include <Utils/Parsing.h>

#include <ostream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <set>

ObjMeshSerializer::ObjMeshSerializer()
    : MeshSerializer()
{
}

ObjMeshSerializer::~ObjMeshSerializer()
{
}

bool ObjMeshSerializer::Load(std::istream& is, std::shared_ptr<Mesh>& mesh)
{
    std::set<std::string> not_supported_feature;

    for (std::string line; std::getline(is, line);)
    {
        if (!line.length()) continue;
        auto tokens = string_split(line);

        if (!tokens.size()) continue;

        auto it = tokens.begin();

        if (*it == "#")
        {
            continue; // skip comments
        }
        else if (*it == "v")
        {
            auto x = static_cast<Real>(::atof((*(++it)).c_str()));
            auto y = static_cast<Real>(::atof((*(++it)).c_str()));
            auto z = static_cast<Real>(::atof((*(++it)).c_str()));

            mesh->AppendPoint(x, y, z);
        }
        else if (*it == "f")
        {
            std::vector<Index> vertex_indices;
            vertex_indices.reserve(tokens.size());

            for (++it; it != tokens.end(); ++it)
            {
                auto index = static_cast<Index>(::atol((*it).c_str()));
                vertex_indices.push_back(index - 1);
            }

            mesh->AppendFace<Polygon>(std::move(vertex_indices));
        }
        else
        {
            not_supported_feature.emplace(*it);
        }
    }

    // print not supported features
    for (const auto& feature : not_supported_feature)
    {
        std::cout << "Warning: Not supported obj feature " << feature << '\n';
    }

    return true;
}


bool ObjMeshSerializer::Save(std::ostream& os, const std::shared_ptr<Mesh>& mesh)
{
    // vertices
    for (Index i{}; i < mesh->NumPoints(); ++i)
    {
        const Vector3 & pt = mesh->GetPosition(i);
        os << "v " << pt.x() << " " << pt.y() << " " << pt.z() << '\n';
    }

    // faces
    for (Index i{}; i < mesh->NumFaces(); ++i)
    {
        /*
                os << "f ";
                for (Index j{}; j < mesh.NumFacePoints(i); ++j)
                {
                    os << mesh.FacePointOffset(i, j) + j << ' ';
                }
                os << '\n'; */
    }

    return true;
}


