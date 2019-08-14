#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

#include <Core/AABBox.h>
#include <Core/Vector3.h>
#include <Geometry/Mesh.h>
#include <Geometry/Triangle.h>

#include <Acceleration/BVH.h>
#include <Serialization/ObjMeshSerializer.h>
#include <Utils/Format.h>

using namespace std;

std::vector<long long> random_range(size_t face_index)
{
    std::vector<long long> result;
    result.reserve(face_index);

    for (size_t i{}; i < face_index; ++i)
    {
        result.push_back(i);
    }

    std::random_shuffle(result.begin(), result.end());
    return result;
}

int main()
{
    std::string data = DATA_DIR;
    std::ifstream if_obj{data + "squab.obj"};
    if (!if_obj.is_open())
    {
        std::cout << "Can not open file!\n";
        return 0;
    }

    ObjMeshSerializer obj_serializer;
    Mesh mesh;
    obj_serializer.Load(if_obj, mesh);

    //
    // Construct BVHAccelerator
    //
    std::vector<const Prim*> prims;
    prims.reserve(mesh.NumFaces());
    for (Index i{}; i < mesh.NumFaces(); ++i)
    {
        prims.push_back(mesh.GetFace(i));
    }

    BVHAccelerator mesh_bvh{prims, 1};
    std::cout << mesh_bvh.MemoryUsage() << std::endl;

    return 0;
}
