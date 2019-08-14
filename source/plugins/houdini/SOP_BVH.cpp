#include <UT/UT_DSOVersion.h>

#include <SOP/SOP_Node.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_Operator.h>
#include <OP/OP_AutoLockInputs.h>
#include <GA/GA_Primitive.h>
#include <PRM/PRM_Range.h>
#include <UT/UT_PerfMonAutoEvent.h>
#include <GU/GU_PrimPoly.h>

#include <Core/Prim.h>
#include <Acceleration/BVH.h>
#include <Utils/Format.h>

#include <iostream>

namespace
{

class PrimPolyWrapper final : public Prim
{
public:
    PrimPolyWrapper(const GU_PrimPoly* poly)
        : Prim()
        , poly_(poly)
    {
    }

    Vector3 Centroid() const final
    {
        auto c = poly_->baryCenter();
        return {c.x(), c.y(), c.z()};
    }

    AABBox Bounds() const final
    {
        UT_BoundingBox b;
        poly_->getBBox(&b);
        return AABBox{ {b.xmin(), b.ymin(), b.zmin()}, {b.xmax(), b.ymax(), b.zmax()} };
    }

private:
    const GU_PrimPoly* poly_;
};


PRM_Name prm_names[] = {
    PRM_Name("maxentries", "Max Entries"),
};

PRM_Default maxentriesDefault(1);
PRM_Range maxentriesRange(PRM_RANGE_RESTRICTED, 1, PRM_RANGE_UI, 100);

PRM_Template myTemplateList[] =
{
    PRM_Template(PRM_INT, 1, &prm_names[0], &maxentriesDefault, 0, &maxentriesRange),
    PRM_Template(),
};

} // namespace

class SOP_BVH : public SOP_Node
{
public:
    SOP_BVH(OP_Network* net, const char* name, OP_Operator* op)
        : SOP_Node(net, name, op)
    {}

    OP_ERROR cookMySop(OP_Context& context) override
    {
        OP_AutoLockInputs inputs(this);
        if (inputs.lock(context) >= UT_ERROR_ABORT)
            return error();

        const GU_Detail* geo = inputGeo(0);

        std::vector<std::unique_ptr<PrimPolyWrapper>> wrappers;
        std::vector<const Prim*> prims;
        wrappers.reserve(geo->getNumPrimitives());
        prims.reserve(geo->getNumPrimitives());

        for (auto it = geo->getPrimitiveRange().begin(); !it.atEnd(); ++it)
        {
            const GA_Primitive* prim = geo->getPrimitive(it.getOffset());
            auto prim_poly = dynamic_cast<const GU_PrimPoly*>(prim);
            if (!prim_poly)
            {
                continue;
            }

            wrappers.emplace_back(std::unique_ptr<PrimPolyWrapper>(new PrimPolyWrapper(prim_poly)));
            prims.push_back(wrappers.back().get());
        }

        // cleanup cached data
        gdp->clearAndDestroy();

        //UT_PerfMonAutoCookEvent bvh_create_envent(this->getUniqueId(), "BVH Construction");
        auto max_entries = evalInt("maxentries", 0, 0);
        BVHAccelerator bvh{ prims, static_cast<Index>(max_entries) };

        const auto bvh_root = bvh.Root();
        if (!bvh_root)
        {
            addError(SOP_MESSAGE, "Root is null, nothing to compute");
            return error();
        }

        std::vector<const BVHNode*> nodes;
        nodes.reserve(bvh.NumNodes());
        nodes.push_back(bvh_root);

        while (!nodes.empty())
        {
            const BVHNode* node = nodes.back();
            nodes.pop_back();

            const auto& bbox = node->GetBBox();

            const auto& min_box = bbox.MinPoint();
            const auto& max_box = bbox.MaxPoint();

            gdp->cube(min_box.x(), max_box.x(),
                      min_box.y(), max_box.y(),
                      min_box.z(), max_box.z());

            if (!node->IsLeaf())
            {
                nodes.push_back(node->GetChild(0));
                nodes.push_back(node->GetChild(1));
            }
        }

        return OP_ERROR();
    }

    static OP_Node* myConstructor(OP_Network* net, const char* name, OP_Operator* op)
    {
        return new SOP_BVH(net, name, op);
    }
};

void newSopOperator(OP_OperatorTable* table)
{
    table->addOperator(new OP_Operator(
        "meshbvh",
        "Mesh BVH",
        SOP_BVH::myConstructor,
        myTemplateList,
        1,
        1,
        0));
}