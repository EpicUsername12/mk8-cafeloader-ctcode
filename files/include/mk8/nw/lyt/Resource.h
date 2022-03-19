#ifndef _NW_LYT_RESOURCE_ACC_HPP
#define _NW_LYT_RESOURCE_ACC_HPP

namespace nw {
namespace lyt {
typedef class MultiArcResourceAccessor MultiArcResourceAccessor;
typedef class ResourceAccessor ResourceAccessor;
} // namespace lyt
} // namespace nw

#include <mk8/ui/UILoader.h>

struct NewLinkedList {
    int size;
    void* mPrev;
    void* mNext;
};

namespace nw {
namespace lyt {

class MultiArcResourceAccessor {
  public:
    void* vtable;
    NewLinkedList array1;
    NewLinkedList array2;
    NewLinkedList array3;

    void* GetResource(uint32_t resType, char const* resName, size_t* pSize);
};

//! TODO: Move UIResourceAccessor back to <mk8/ui>

class ResourceAccessor {
  public:
    nw::lyt::MultiArcResourceAccessor mArcRA;
    ui::UILoader* loader; // wtf
};
} // namespace lyt
} // namespace nw

#endif