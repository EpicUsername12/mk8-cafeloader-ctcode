#include "init.h"

char BootHeapData[0xD49000];
char MenuSubHeapData[0xD79000];

/* libgcc memcpy */
void* memcpy(void* dest, const void* src, size_t len) {
    return OSBlockMove(dest, src, len, 0);
}

extern "C" uint32_t MK8_OSDynLoad_Acquire;
extern "C" uint32_t MK8_OSDynLoad_FindExport;

OsSpecifics osSpecifics;

extern "C" void call_ctors() {

    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;

    OS_SPECIFICS->addr_OSDynLoad_Acquire = (u32)(MK8_OSDynLoad_Acquire & 0x03FFFFFC);
    OS_SPECIFICS->addr_OSDynLoad_FindExport = (u32)(MK8_OSDynLoad_FindExport & 0x03FFFFFC);

    if (!(MK8_OSDynLoad_Acquire & 2))
        OS_SPECIFICS->addr_OSDynLoad_Acquire += (u32)&MK8_OSDynLoad_Acquire;
    if (!(MK8_OSDynLoad_FindExport & 2))
        OS_SPECIFICS->addr_OSDynLoad_FindExport += (u32)&MK8_OSDynLoad_FindExport;

    InitOSFunctionPointers();
    InitGX2FunctionPointers();
    InitACTFunctionPointers();
    InitFSFunctionPointers();

    LOG("Hello from playground.\n");
}

ui::Control_CupButton* cupButtons[6];
static char* sExtendedCupList[] = { "L_CupIcon_12", "L_CupIcon_13", "L_CupIcon_14",
                                    "L_CupIcon_15", "L_CupIcon_16", "L_CupIcon_17" };

ui::Control_NXBtnL* L_Btn = nullptr;
ui::Control_NXBtnR* R_Btn = nullptr;
ui::Input_Key* X_Btn = nullptr;
bool sIsInChargerPageAnim = false;
bool sChargerCups = false;

extern "C" void Page_CourseBase_LoadPanes(ui::Page_CourseBase* _this, ui::UIControl* mainControl, bool r5) {

    /* Patch save file */
    sys::SaveDataManager* saveDataMgr = sys::SystemEngine::getEngine()->mSaveDataMgr;
    void* saveDataPtr = saveDataMgr->getRealUserSaveDataPtr(nn_act_GetSlotNo());

    /* Unlock all 8 base cups */
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A28) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A29) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2A) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2B) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2C) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2D) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2E) = 3;
    *saveDataMgr->calculateFlagPtrFromOffset(saveDataPtr, 0x1A2F) = 3;

    _this->LoadPanes(mainControl, r5);

    if (_this->pageID == ui::Page_CourseVS::ID) {
        for (int i = 0; i < 6; i++) {
            ui::Control_CupButton* btn = new ui::Control_CupButton(r5);
            _this->createControl_(btn, mainControl, sExtendedCupList[i]);
            cupButtons[i] = btn;
        }

        L_Btn = new ui::Control_NXBtnL(ui::Control_NXBtnL::TEXTURE_L);
        R_Btn = new ui::Control_NXBtnR(ui::Control_NXBtnR::TEXTURE_R);
        _this->createControl_(L_Btn, mainControl, "L_LBtn_00");
        _this->createControl_(R_Btn, mainControl, "L_RBtn_00");
        X_Btn = new ui::Input_Key();
        X_Btn->requiredInput = MK8_INPUT_PLUS;
        _this->pushInput(*X_Btn);
    }

    nw::lyt::Pane* p1 = mainControl->findPane("L_LBtn_00");
    nw::lyt::Pane* p2 = mainControl->findPane("L_RBtn_00");
    nw::lyt::Pane* p3 = mainControl->findPane("P_UndrBase_L_00");
    nw::lyt::Pane* p4 = mainControl->findPane("P_UndrBase_R_00");
    LOG("%p %p %p %p\n", p1, p2, p3, p4);
    LOG("0x%02x 0x%02x 0x%02x 0x%02x\n", p1->flag & 1, p2->flag & 1, p3->flag & 1, p4->flag & 1);
}

extern "C" void Page_CourseBase_LoadAnimations(ui::Page_CourseBase* _this, ui::UIControl* mainControl) {

    _this->LoadAnimations(mainControl);

    ui::UIAnimator* AnimatorCupIO = _this->createAnimator(6, mainControl, 2);
    AnimatorCupIO->bind(0, "CupIn");
    AnimatorCupIO->bind(1, "CupOut");

    ui::UIAnimator* IconVisibility = _this->createAnimator(7, mainControl, 1);
    IconVisibility->bind(0, "ChangeIconVisible");

    ui::UIAnimator* BoardColor = _this->createAnimator(8, mainControl, 2);
    BoardColor->bind(0, "BGBoardChangeWtoB");
    BoardColor->bind(1, "BGBoardChangeBtoW");

    ui::UIAnimator* Loop = _this->createAnimator(9, mainControl, 1);
    BoardColor->bind(0, "Loop");

    ui::UIAnimator* LR_Btn = _this->createAnimator(10, mainControl, 2);
    LR_Btn->bind(0, "LBtnDown");
    LR_Btn->bind(1, "RBtnDown");

    _this->animators[7]->stop(0, 1.0f); // ChangeIconVisible
}

// clang-format off
// Also yes, this is how nintendo does it.
static const int sCupRealIDs[12] = {
    0, 1, 2, 3, 8, 10,
    4, 5, 6, 7, 9, 11,
};
// clang-format on

// sub_25B9B44
extern "C" void hook_Page_CourseBase_initialize(ui::Page_CourseBase* _this) {

    _this->initialize();

    for (int i = 0; i < 12; i++) {
        _this->cupIcons[i]->animators[2]->stop(0, sCupRealIDs[i]); // IconChange
    }
    for (int i = 0; i < 6; i++) {
        cupButtons[i]->animators[2]->stop(0, i + 12); // IconChange
    }
}

extern "C" void hook_Page_Bg_onCreate(ui::Page_Bg* _this) {

    _this->onCreate();
    ui::UIAnimator* BgColor = _this->createAnimator(6, _this->mMainControl, 1);
    BgColor->bind(0, "BgColor");
}

extern "C" void hook_Page_CourseVS_toOut(ui::Page_CourseVS* _this) {
    _this->toOut();

    if (sChargerCups) {
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
    }
}

extern "C" void hook_Page_CourseVS_toIn(ui::Page_CourseVS* _this, ui::UIFlow* flow) {
    _this->toIn(flow);

    if (sChargerCups) {
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor

        for (int i = 0; i < 12; i++) {
            _this->cupIcons[i]->animators[2]->stop(0, 12 + i); // IconChange
        }
        for (int i = 0; i < 6; i++) {
            cupButtons[i]->animators[2]->stop(0, sCupRealIDs[i]); // IconChange
        }
    }
}

extern "C" void hook_Page_CourseVS_onHandler(ui::Page_CourseVS* _this, ui::UIEvent& event) {

    if (sIsInChargerPageAnim) {
        return;
    }

    _this->onHandler(event);

    if (sChargerCups) {
        for (int i = 0; i < 12; i++) {
            if (event.cursor_event.sourceControl == _this->cupIcons[i]) {
                _this->animators[3]->stop(0, i + 12.0f); // CupIconLineChange_00
            }
        }
    }

    if (event.m_InputValue == MK8_INPUT_L) {
        _this->animators[10]->play_(0); // LBtnDown
        _this->animators[6]->play_(1);  // CupOut
        if (sChargerCups) {
            _this->animators[8]->play_(1); // BGBoardChangeBtoW
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        } else {
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
            _this->animators[8]->play_(0);                  // BGBoardChangeWtoB
        }
        sIsInChargerPageAnim = true;
    } else if (event.m_InputValue == MK8_INPUT_R) {
        _this->animators[10]->play_(1); // RBtnDown
        _this->animators[6]->play_(1);  // CupOut
        if (sChargerCups) {
            _this->animators[8]->play_(1); // BGBoardChangeBtoW
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        } else {
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
            _this->animators[8]->play_(0);                  // BGBoardChangeWtoB
        }
        sIsInChargerPageAnim = true;
    }
}

extern "C" void hook_Page_CourseVS_onCalc(ui::Page_CourseBase* _this) {

    _this->onCalc();

    if (_this->pageID == ui::Page_CourseVS::ID) {
        if (sIsInChargerPageAnim) {

            // If CupOut done, and CupIn ready, do CupIn
            if (_this->animators[6]->isEnd(1)) {

                if (!sChargerCups) {
                    for (int i = 0; i < 12; i++) {
                        _this->cupIcons[i]->animators[2]->stop(0, 12 + i); // IconChange
                    }
                    for (int i = 0; i < 6; i++) {
                        cupButtons[i]->animators[2]->stop(0, sCupRealIDs[i]); // IconChange
                    }
                    sChargerCups = true;
                } else {
                    for (int i = 0; i < 12; i++) {
                        _this->cupIcons[i]->animators[2]->stop(0, sCupRealIDs[i]); // IconChange
                    }
                    for (int i = 0; i < 6; i++) {
                        cupButtons[i]->animators[2]->stop(0, 12 + i); // IconChange
                    }
                    sChargerCups = false;
                }

                // Change bg color.
                _this->animators[6]->play_(0);
                LOG("Cup out done, doing cup in\n");
            }

            // If CupOut done and CupIn done, we're done.
            if (_this->animators[6]->isEnd(0)) {
                LOG("Cup out done, cup in done too\n");
                sIsInChargerPageAnim = false;
            }
        }
    }
}

extern "C" sead::Heap* hook_ui_Heap_Boot_onCreateHeap(ui::Heap_Boot* _this) {
    sead::Heap* ret = sead::ExpHeap::tryCreate((void*)BootHeapData, 0xD49000, "UIHeap_Boot", false);
    return ret;
}

extern "C" sead::Heap* hook_ui_Heap_MenuSub_onCreateHeap(ui::UIHeap* _this) {
    sead::Heap* ret = sead::ExpHeap::tryCreate((void*)MenuSubHeapData, 0xD79000, "UIHeap_MenuSub", false);
    return ret;
}