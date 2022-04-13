#ifndef _UI_CONTROL_BUTTON_HPP
#define _UI_CONTROL_BUTTON_HPP

#include <basis/seadTypes.h>
#include <stdint.h>

#include <heap/seadDisposer.h>
#include <mk8/ui/UIControl.h>
#include <mk8/ui/UIInput.h>

namespace ui {
class Control_Button : public UIControl, public sead::IDisposer {

    SEAD_RTTI_OVERRIDE(Control_Button, UIControl)

    enum ESeType {
        I_HAVE_NO_IDEA = 0,
    };

  public:
    Input_Key inputKey;
    Input_Touch inputTouch;
    UIFlow* flow;
    char field_DC;
    char field_DD;
    char field_DE;
    char field_DF;
    int field_E0[4];
    int field_F0;

    Control_Button();

    virtual void onCreate();
    virtual void unk1() {
    }
    virtual void onIn();
    virtual void onCalc();
    virtual void unk2() {
    }

    virtual void onDrawDummy(void* UIDrawInfo) {
    }
    virtual void onHandler(ui::UIEvent const& event);
    void onHandlerImpl(ui::UIEvent const& event);

    virtual ~Control_Button();
    virtual void getSLinkName(sead::FixedSafeString<64>*);
    virtual void getSLinkSeName(ESeType, sead::FixedSafeString<32>*);
    virtual void startSe_(ESeType);
    virtual void selectOn(ui::UIEvent const&);
    virtual void selectOff(ui::UIEvent const&);
    virtual void decide(ui::UIEvent const&);
    virtual void unk3();
    virtual void cancel(int);
    virtual void unk4();
    virtual void unk5();
    virtual void unk6();
    virtual void unk7();
    virtual void unk8();
    virtual void unk9();
    virtual void animOn();
    virtual void animOff();
    virtual void animKeepOn();
    virtual void animKeepOff();
    virtual void animDecide();
    virtual void animCancel();
};
} // namespace ui

static_assert(sizeof(ui::Control_Button) == 0xF4, "Class doesn't match game class size");

#endif