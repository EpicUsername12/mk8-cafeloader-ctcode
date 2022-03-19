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

    void onHandler(ui::UIEvent const& event);
};
} // namespace ui

static_assert(sizeof(ui::Control_Button) == 0xF4, "Class doesn't match game class size");

#endif