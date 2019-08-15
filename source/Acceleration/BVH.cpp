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

#include "BVH.h"

#include <Foundation/Math.h>
#include <Foundation/Prim.h>

#include <algorithm>

using Range = BVHNode::Range;
using SplitMethod = BVHAccelerator::SplitMethod;

namespace
{

///
/// TODO How long stack can go with imbalanced tree?
///
template <typename T, Index S = 256> class Stack
{
public:
    Stack() = default;

    void Push(const T& v) { s[size++] = v; }
    void Push(T&& v) { s[size++] = std::move(v); }

    T Pop() { return s[--size]; }
    T Back() { return s[size-1]; }

    Index Size() const { return size; }
    bool Empty() const { return size == 0; }

    void Clear() { size = 0; }

private:
    T s[S]{};
    Index size{};
};

struct PrimCache
{
    PrimCache(const Prim& prim, Index i)
        : index(i)
        , centroid(prim.Centroid())
        , bbox(prim.Bounds())
    {
    }

    PrimCache(const PrimCache&) = default;
    PrimCache(PrimCache&&) = default;

    PrimCache& operator=(const PrimCache&) = default;
    PrimCache& operator=(PrimCache&&) = default;

    Index index;
    Vector3 centroid;
    AABBox bbox;
};

std::vector<PrimCache> create_prim_cache(const std::vector<const Prim*>& prims, AABBox& centroid_bbox)
{
    std::vector<PrimCache> entries;
    entries.reserve(prims.size());

    // fill entries and compute box

    for (auto it = prims.begin(); it != prims.end(); ++it)
    {
        const Prim* prim = *it;
        entries.emplace_back(*prim, std::distance(prims.begin(), it));
        centroid_bbox = ::Union(centroid_bbox, entries.back().bbox);
    }

    return entries;
}

// TODO move as a method of BVH node
void split_bbox(const AABBox& bbox, const Vector3 & p, Index axis, AABBox(&bboxes)[2])
{
    Vector3 l_max = bbox.MaxPoint();
    l_max[axis] = p[axis];

    Vector3 r_min = bbox.MinPoint();
    r_min[axis] = p[axis];

    bboxes[0] = AABBox{ bbox.MinPoint(), l_max };
    bboxes[1] = AABBox{ r_min, bbox.MaxPoint() };
}
    
} // namespace

BVHNode::BVHNode(Range r, AABBox b)
    : range_(r)
    , bbox_(b)
{
}

BVHAccelerator::BVHAccelerator(const std::vector<const Prim *>& prims,
                               Index max_prims,
                               SplitMethod split_method)
{
    auto num_prims = static_cast<Index>(prims.size());
    if (num_prims == 0)
    {
        return;
    }

    max_prims = max_prims == 0 ? 1 : max_prims;

    // allocate space for all nodes
    nodes_.reserve(2 * num_prims - 1);

    // create root bvh node
    AABBox centroid_bbox;
    std::vector<PrimCache> entries = create_prim_cache(prims, centroid_bbox);
    nodes_.emplace_back(Range{ 0, num_prims }, centroid_bbox);

    Stack<BVHNode*, 256> stack;
    stack.Push(&nodes_.back());

    while (!stack.Empty())
    {
        // For DFS traversal we keep non leaf nodes on the stack
        // Their bbox will be updated after drilling to the children is done
        BVHNode* node = stack.Back();

        // Sum bounding boxes for parent node
        if (!node->IsLeaf())
        {
            AABBox children_bbox;
            for (Index i{}; i < node->NumChildren(); ++i)
            {
                children_bbox = ::Union(children_bbox, node->GetChild(i)->GetBBox());
            }
            node->GetBBox() = children_bbox;
            stack.Pop();
            continue;
        }

        const Range& node_range = node->GetRange();
        const Index num_node_entries = node->NumEntries();

        // BVHNode leaf can group few entries, compute union for all of them from the range
        if (num_node_entries <= max_prims)
        {
            AABBox leaf_bbox;
            for (auto i = node_range.start; i < node_range.end; ++i)
            {
                leaf_bbox = ::Union(leaf_bbox, entries[i].bbox);
            }
            node->GetBBox() = leaf_bbox;
            stack.Pop();
            continue;
        }

        // Split Bounds into left and right
        const AABBox& bbox = node->GetBBox();
        const Index max_extent = bbox.MaxExtent();

        auto centroid_cmp = [max_extent](const PrimCache& l, const PrimCache& r)
        {
            return l.centroid[max_extent] < r.centroid[max_extent];
        };

        // partial sort along longest extent
        const Index median_index = node_range.start + static_cast<Index>(0.5 * num_node_entries);
        std::nth_element(entries.begin() + node_range.start,
                         entries.begin() + median_index,
                         entries.begin() + node_range.end,
                         centroid_cmp);

        // split to L - R
        Range lr_range[2] = { { node_range.start, median_index }, { median_index, node_range.end } };

        // median for box split
        AABBox lr_bbox[2];
        const PrimCache& median = entries[median_index];
        split_bbox(bbox, median.centroid, max_extent, lr_bbox);

        // append children
        for (Index c{}; c < 2; ++c)
        {
            //auto new_size = lr_range[c].end - lr_range[c].start;

            nodes_.emplace_back(lr_range[c], lr_bbox[c]);
            BVHNode* child = &nodes_.back();
            node->SetChild(c, child);

            // put on top
            stack.Push(child);
        }
    }

    // move all nodes to
}
