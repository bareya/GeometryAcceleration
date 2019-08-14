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

#ifndef BVH_H
#define BVH_H

#include <Core/AABBox.h>

#include <vector>
#include <memory>

class Prim;
class Face;

///
/// BVHNode
///
class BVHNode
{
public:
    struct Range
    {
        Index start{INDEX_INVALID};
        Index end{INDEX_INVALID};
    };

    // TODO this has to be replaced by constructors that 
    // compute those features
    BVHNode(Range r, AABBox b);
    
    BVHNode(const BVHNode&) = default;
    BVHNode(BVHNode&&) = default;

    BVHNode& operator=(const BVHNode&) = default;
    BVHNode& operator=(BVHNode&&) = default;

    const Range& GetRange() const { return range_; }
    Index NumEntries() const { return range_.end - range_.start; }

    const AABBox& GetBBox() const { return bbox_; }
    AABBox& GetBBox() { return bbox_; }
    void SetBBox(AABBox b) { bbox_ = b; }

    const BVHNode* GetChild(Index i) const { return children_[i]; }
    BVHNode* GetChild(Index i) { return children_[i]; }
    bool IsLeaf() const { return children_[0] == nullptr && children_[1] == nullptr; }
    Index NumChildren() const { return 2; }

    void SetChild(Index i, BVHNode* child) { children_[i] = child; }

private:
    Range range_;
    AABBox bbox_;
    BVHNode* children_[2]{};
};

///
///
///
class BVHAccelerator
{
public:
    enum class SplitMethod
    {
        MidPoint,
        Median,
        //SurfaceAreaHeuristic
    };

    BVHAccelerator(const std::vector<const Prim*>& prims, Index max_prims = 1);

    BVHAccelerator(const BVHAccelerator&) = delete;
    BVHAccelerator(BVHAccelerator&&) = delete;

    BVHAccelerator& operator=(const BVHAccelerator&) = delete;
    BVHAccelerator& operator=(BVHAccelerator&&) = delete;

    Index NumNodes() const { return nodes_.size(); }
    const BVHNode* Root() const { return nodes_.empty() ? nullptr : &nodes_.front(); }

    Index MemoryUsage() const
    {
        return sizeof(BVHNode) * nodes_.size() + sizeof(BVHAccelerator);
    }

private:
    std::vector<BVHNode> nodes_;
};

#endif // BVH_H
