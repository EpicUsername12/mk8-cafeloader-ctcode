#ifndef _UI_UIPAGE_HPP
#define _UI_UIPAGE_HPP

namespace ui {
typedef class UIPage UIPage;
}

#include <basis/seadTypes.h>
#include <stdint.h>

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>

namespace ui {
typedef class UIHeap UIHeap;
typedef class UIEvent UIEvent;
} // namespace ui

#include <mk8/ui/UIAnimator.h>
#include <mk8/ui/UIControl.h>
#include <mk8/ui/UICursor.h>
#include <mk8/ui/UIFlow.h>
#include <mk8/ui/UIHeap.h>
#include <mk8/ui/UIEvent.h>
#include <mk8/ui/UILoader.h>
#include <mk8/ui/UIInput.h>

struct PTMF {
    uint32_t vtable;
    uint32_t instance;
    int16_t field_8;
    int16_t field_A;
    uint32_t funcPtr;
};

namespace ui {

class UIPage {

    SEAD_RTTI_BASE(UIPage)

  public:
    class StateInfo {
        int field_00;
        int state;
        int field_08;
        int field_0C;
        PTMF func;
        int field_20;
    };

    int layerID;
    int pageID;
    UIHeap* heap;
    UILoader* loader;
    int field_10;
    int field_14;
    int field_18;
    bool hasControls;
    sead::PtrArray<UIControl> controls;
    bool hasControls2;
    sead::PtrArray<UIControl> controls2;
    int field_3C;
    sead::Buffer<UIAnimator*> animators;
    int animatorCount;
    StateInfo stateInfo;
    int field_70;
    UISceneFlow* flow;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    int m_pUIControlSlider;
    int field_90;
    sead::PtrArray<UIInput*> pushedInputs;
    int field_A0;
    int input; // binary value
    int field_A8;
    UICursor* cursor;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;

    UIPage();

    void toPrepare(UIFlow* flow);

    void toExit();

    void toIn(UIFlow* flow);

    void toOut();

    void loadControl_(UIControl* pOutControl, int unk_5, sead::SafeStringBase<char> const& str);

    void createControl_(UIControl* pOutControl, UIControl* mainControl, sead::SafeStringBase<char> const& str);

    void pushInput(ui::UIInput& input);

    void toPage(ui::UIFlow* pFlow);

    void onCreate();

    int onHandler(ui::UIEvent& event);

    UIAnimator* createAnimator(int idx, UIControl* control, int numAnims);
};
} // namespace ui

static_assert(sizeof(ui::UIPage) == 0xC8, "Class doesn't match game class size");

#endif