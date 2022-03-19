#ifndef _UI_ANIMATOR_H
#define _UI_ANIMATOR_H

namespace ui {
typedef class UIAnimator UIAnimator;
typedef class UIAnimation UIAnimation;
} // namespace ui

#include <basis/seadTypes.h>

#include <mk8/nw/lyt/Animation.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <mk8/ui/UIControl.h>

namespace ui {

// inlined ctor
class UIAnimation {
  public:
    nw::lyt::GroupAnimator* groupAnimator;
    float field_04;
    int field_08;
};

class UIAnimator {
  public:
    UIControl* control;
    int field_04;
    sead::Buffer<UIAnimation*> animations;

    void bind(int index, sead::SafeStringBase<char> const& parent, sead::SafeStringBase<char> const& child);
};

} // namespace ui

static_assert(sizeof(ui::UIAnimation) == 0x0C, "Class doesn't match game class size");
static_assert(sizeof(ui::UIAnimator) == 0x10, "Class doesn't match game class size");

#endif