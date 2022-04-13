#include "course_ext.h"
#include <dynamic_libs/aoc_functions.h>

CUP0* sCup0 = nullptr;
char* gTrackPathsBackup[NUM_TRACKS];
const char* ui::sExtendedCupPaneNames[] = { "L_CupIcon_12", "L_CupIcon_13", "L_CupIcon_14",
                                            "L_CupIcon_15", "L_CupIcon_16", "L_CupIcon_17" };

int nextCupPage(ui::Page_CourseExt* ext) {
    if (ext->mCupPage == sCup0->getNumPages()) {
        return 0;
    } else {
        return ext->mCupPage + 1;
    }
}

void Page_CourseBase_toNextCupPage(ui::Page_CourseExt* ext) {
    ext->mCupPage = nextCupPage(ext);
}

extern "C" void hook_Page_Bg_onCreate(ui::Page_Bg* _this) {
    _this->onCreate();
    ui::UIAnimator* BgColor = _this->createAnimator(6, _this->mMainControl, 1);
    BgColor->bind(0, "BgColor");
}

extern "C" void Page_CourseBase_onCreateExtension(ui::Page_CourseBase* _this) {

    ui::getPageExtension(_this)->Constructor();

    if (!sCup0) {
        messagePatcher = new MessagePatcher();
        messagePatcher->Initialize();
        sCup0 = new CUP0();
        for (int i = 0; i < NUM_TRACKS; i++) {
            gTrackPathsBackup[i] = gTrackPaths[i];
        }
    }

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

    bool unk = false;
    if (_this->pageID == ui::Page_CourseGP::ID) {
        unk = true;
    }

    ui::Page_CourseExt* ext = ui::getPageExtension(_this);
    for (int i = 0; i < 6; i++) {
        ui::Control_CupButton* btn = new ui::Control_CupButton(unk);
        _this->createControl_(btn, _this->mainControl, ui::sExtendedCupPaneNames[i]);
        ext->mUpperCupButtons[i] = btn;
    }

    ext->mBtnL = new ui::Control_NXBtnL(ui::Control_NXBtnL::TEXTURE_L);
    ext->mBtnR = new ui::Control_NXBtnR(ui::Control_NXBtnR::TEXTURE_R);
    _this->createControl_(ext->mBtnL, _this->mainControl, "L_LBtn_00");
    _this->createControl_(ext->mBtnR, _this->mainControl, "L_RBtn_00");

    ui::UIAnimator* AnimatorCupIO = _this->createAnimator(6, _this->mainControl, 2);
    AnimatorCupIO->bind(0, "CupIn");
    AnimatorCupIO->bind(1, "CupOut");

    ui::UIAnimator* IconVisibility = _this->createAnimator(7, _this->mainControl, 1);
    IconVisibility->bind(0, "ChangeIconVisible");

    ui::UIAnimator* BoardColor = _this->createAnimator(8, _this->mainControl, 2);
    BoardColor->bind(0, "BGBoardChangeWtoB");
    BoardColor->bind(1, "BGBoardChangeBtoW");

    ui::UIAnimator* Loop = _this->createAnimator(9, _this->mainControl, 1);
    BoardColor->bind(0, "Loop");

    ui::UIAnimator* LR_Btn = _this->createAnimator(10, _this->mainControl, 2);
    LR_Btn->bind(0, "LBtnDown");
    LR_Btn->bind(1, "RBtnDown");

    _this->animators[7]->stop(0, 1.0f); // ChangeIconVisible
}

// clang-format off
// Also yes, this is how nintendo does it. (but inlined, and on the stack)
static const int ui::sCupRealIDs[12] = {
    0, 1, 2, 3, 8, 10,
    4, 5, 6, 7, 9, 11,
};
// clang-format on

extern "C" void hook_Page_CourseBase_initialize(ui::Page_CourseBase* _this) {

    _this->initialize();
    ui::Page_CourseExt* ext = ui::getPageExtension(_this);

    for (int i = 0; i < 12; i++)
        _this->cupIcons[i]->animators[2]->stop(0, ui::sCupRealIDs[i]); // IconChange

    for (int i = 0; i < 6; i++)
        ext->mUpperCupButtons[i]->animators[2]->stop(0, i + 12); // IconChange
}

void Page_CourseBase_changeTrackIcons(ui::Page_CourseBase* page, ui::Page_CourseExt* ext) {

    ui::Heap_Common* heap = ui::Heap_Common::getHeap();
    int cupId = heap->courseData->courseRelatedData.currentlySelectedCup;
    if (cupId < 0) // in case it's called from outside the cup selection page
        return;

    CUP0::Cup* ctCup = sCup0->getCup(ext->mCupPage, cupId);
    if (ctCup && ext->mCupPage > 0 && cupId < 12) {
        for (int i = 0; i < 4; i++) {
            page->courseBtn[i]->setTexture(page->courseBtn[i]->coursePictPane, ctCup->mTrackTextures[i], 1);
            page->courseBtn[i]->setVisible(page->courseBtn[i]->coursePictPane, 1);
            page->courseBtn[i]->setVisible(page->courseBtn[i]->courseMoviePane, 0);
            page->courseBtn[i]->setMessage(page->courseBtn[i]->courseNameTextPane, ctCup->mTrackNameIds[i]);
            if (ctCup->mTrackRetroNameIds[i] > 0) {
                page->courseBtn[i]->setVisible(page->courseBtn[i]->classicNameTextPane, 1);
                page->courseBtn[i]->setMessage(page->courseBtn[i]->classicNameTextPane, ctCup->mTrackRetroNameIds[i]);
            } else {
                page->courseBtn[i]->setVisible(page->courseBtn[i]->classicNameTextPane, 0);
            }
            page->mainControl->setMessage(page->cupNameTextPane, ctCup->mNameId);
            gTrackPaths[heap->courseData->courseList.cups[cupId].courses[i].id] = ctCup->mTrackPaths[i];
        }
    }

    if (ext->mCupPage == 0) {
        for (int i = 0; i < 4; i++) {
            gTrackPaths[heap->courseData->courseList.cups[cupId].courses[i].id] =
                gTrackPathsBackup[heap->courseData->courseList.cups[cupId].courses[i].id];

            page->courseBtn[i]->setCourse(heap->courseData->courseList.cups[cupId].courses[i], nullptr);
            page->mainControl->setMessage(page->cupNameTextPane, ui::sCupNameIDs[cupId]);
        }
    }
}

void Page_CourseBase_changeCupIcons(ui::Page_CourseBase* _this, ui::Page_CourseExt* ext) {

    // Change cup icons
    for (int i = 0; i < 12; i++) {
        if (ext->mCupPage == 0) {
            _this->cupIcons[i]->animators[2]->stop(0, ui::sCupRealIDs[i]); // IconChange
        } else {
            int cupId = (ext->mCupPage == 1) ? i : ui::sCupRealIDs[i];
            if (sCup0->getCup(ext->mCupPage, cupId)) {
                int frame = sCup0->getCup(ext->mCupPage, cupId)->mIconChangeFrame;
                _this->cupIcons[i]->animators[2]->stop(0, frame); // IconChange
            } else {
                _this->cupIcons[i]->animators[2]->stop(0, ui::sCupRealIDs[i]); // IconChange
            }
        }
    }

    // Change upper cups icons
    static int sBottomCups[6] = { 4, 5, 6, 7, 9, 11 };
    for (int i = 0; i < 6; i++) {
        if (sCup0->getCup(nextCupPage(ext), sBottomCups[i])) {
            int frame = sCup0->getCup(nextCupPage(ext), sBottomCups[i])->mIconChangeFrame;
            ext->mUpperCupButtons[i]->animators[2]->stop(0, frame); // IconChange
        } else {
            ext->mUpperCupButtons[i]->animators[2]->stop(0, ui::sCupRealIDs[i]); // IconChange
        }
    }
}

void Page_CourseBase_onCalcExtension(ui::Page_CourseBase* _this) {
    ui::Page_CourseExt* ext = ui::getPageExtension(_this);
    if (ext->mIsInChargerPageAnim) {
        // If CupOut done, and CupIn ready, do CupIn
        if (_this->animators[6]->isEnd(1)) {
            Page_CourseBase_changeCupIcons(_this, ext);
            Page_CourseBase_changeTrackIcons(_this, ext);
            _this->animators[6]->play_(0); // CupIn
        }

        if (_this->animators[6]->isEnd(0)) {
            ext->mIsInChargerPageAnim = false;
        }
    }
}

bool Page_CourseBase_pre_onHandleExtension(ui::Page_CourseBase* _this, ui::Page_CourseExt* ext, ui::UIEvent& event) {
    if (ext->mCupPage == 1) { // MK8DX Booster Cup page
        for (int i = 0; i < 4; i++) {
            if ((event.cursor_event.sourceControl == _this->courseBtn[i]) && (event.m_InputValue <= MK8_INPUT_A)) {
                int cupId = ui::Heap_Common::getHeap()->courseData->courseRelatedData.currentlySelectedCup;
                _this->cursor->selectOn(0, cupId, 0, 1);
                return false;
            }
        }
        for (int i = 0; i < 12; i++) {
            if ((event.cursor_event.sourceControl == _this->cupIcons[i]) && (event.m_InputValue <= MK8_INPUT_A)) {
                event.m_InputValue = MK8_INPUT_X; // Cancel event indirectly
                event.cursor_event.sourceControl = nullptr;
                audio::utl::startSound2D("SE_SYS_CURSOR_EMPTY");
                return true;
            }
        }
    }
    return true;
}

void Page_CourseBase_onHandleExtension(ui::Page_CourseBase* _this, ui::Page_CourseExt* ext, ui::UIEvent& event) {

    if (_this->pageID == ui::Page_CourseWiFi::ID && !gIsOnlineToggled) {
        return;
    }

    if (event.m_InputValue == MK8_INPUT_L) {
        _this->animators[10]->play_(0); // LBtnDown
    } else if (event.m_InputValue == MK8_INPUT_R) {
        _this->animators[10]->play_(1); // RBtnDown
    }

    if ((event.m_InputValue == MK8_INPUT_L) || (event.m_InputValue == MK8_INPUT_R)) {

        Page_CourseBase_toNextCupPage(ext);
        audio::utl::startSound2D("SE_SYS_CMN_CURSOR");

        _this->animators[6]->play_(1); // CupOut
        if (ext->mCupPage == 0) {
            _this->animators[8]->play_(1); // BGBoardChangeBtoW
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        } else {
            _this->animators[8]->play_(0); // BGBoardChangeWtoB
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        }
        ext->mIsInChargerPageAnim = true;
    }

    if (ext->mCupPage != 0) {
        for (int i = 0; i < 12; i++) {
            if (event.cursor_event.sourceControl == _this->cupIcons[i]) {
                _this->animators[3]->stop(0, i + 12.0f); // CupIconLineChange_00
            }
        }
    }

    Page_CourseBase_changeTrackIcons(_this, ext);

    if (_this->pageID == ui::Page_CourseWiFi::ID && gIsOnlineToggled) {
        if (!event.cursor_event.sourceControl || event.cursor_event.unk != 2) {
            return;
        }

        /* Selected a track (because ControlID == CourseButton) */
        if (event.cursor_event.controlId - 12 < 4) {

            enl::PeerManagerCommon* peerMgr = enl::Framework::sFrameworkInstance->m_PeerManager;
            signed char bufferId = peerMgr->getBufferIDByUniqueID(peerMgr->m_SelfPeer);

            NetworkData_CTGP* ctgpTranspData = (NetworkData_CTGP*)NetworkTransporter_CTGP::sInstance->getSendData();

            sead::PtrArray<enl::SimpleIDInfo>* stationGroupArray =
                peerMgr->getStationGroupArrayByUniqueID(peerMgr->m_SelfPeer);

            LOG(CONSOLE_ID " Voted page %d !\n", ext->mCupPage);
            for (int i = 0; i < stationGroupArray->size(); i++) {
                ctgpTranspData->setVotePage(stationGroupArray->at(i)->mUniqueId, ext->mCupPage);
            }
        }
    }
}

void Page_CourseBase_toOutExtension(ui::Page_CourseBase* _this) {
    ui::Page_CourseExt* ext = ui::getPageExtension(_this);
    if (ext->mCupPage != 0) {
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
    }
}

extern "C" void hook_Page_TopMenu_toIn(ui::UIPage* _this, ui::UIFlow* flow) {
    _this->toIn(flow);
    ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
    ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
}

void Page_CourseBase_toInExtension(ui::Page_CourseBase* _this, ui::UIFlow* pFlow) {
    ui::Page_CourseExt* ext = ui::getPageExtension(_this);
    Page_CourseBase_changeCupIcons(_this, ext);
    Page_CourseBase_changeTrackIcons(_this, ext);
    if (ext->mCupPage != 0) {
        _this->animators[8]->play_(0); // BGBoardChangeWtoB
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
    }
}

/* --------------------------------------------------------------------- */

sead::ExpHeap* extHeap = nullptr;
sead::Heap* extHeapLoad() {
    if (!extHeap) {
        extHeap = sead::ExpHeap::tryCreate(MEMAllocFromDefaultHeapEx(0x120000, 4), 0x120000, "Extension Heap", false);
    }
    sead::Heap* backup_heap = sead::HeapMgr::instance()->getCurrentHeap();
    sead::HeapMgr::instance()->setCurrentHeap_(extHeap);
    return backup_heap;
}

void extHeapUnload(sead::Heap* backup) {
    sead::HeapMgr::instance()->setCurrentHeap_(backup);
}

extern "C" void hook_ui_Page_CourseGP_onCreate(ui::Page_CourseGP_Ext* _this) {
    sead::Heap* backup = extHeapLoad();
    _this->onCreate();
    Page_CourseBase_onCreateExtension(_this);
    extHeapUnload(backup);
}

extern "C" void hook_ui_Page_CourseVS_onCreate(ui::Page_CourseVS_Ext* _this) {
    sead::Heap* backup = extHeapLoad();
    _this->onCreate();
    Page_CourseBase_onCreateExtension(_this);
    extHeapUnload(backup);
}

extern "C" void hook_ui_Page_CourseWiFi_onCreate(ui::Page_CourseWiFi_Ext* _this) {
    sead::Heap* backup = extHeapLoad();
    _this->onCreate();
    Page_CourseBase_onCreateExtension(_this);
    extHeapUnload(backup);
}

/* --------------------------------------------------------------------- */

extern "C" void hook_Page_CourseGP_onHandler(ui::Page_CourseGP_Ext* _this, ui::UIEvent& event) {
    if (_this->mExtension.mIsInChargerPageAnim)
        return;

    if (Page_CourseBase_pre_onHandleExtension(_this, &_this->mExtension, event))
        _this->onHandler(event);

    Page_CourseBase_onHandleExtension(_this, &_this->mExtension, event);
}

extern "C" void hook_Page_CourseVS_onHandler(ui::Page_CourseVS_Ext* _this, ui::UIEvent& event) {
    if (_this->mExtension.mIsInChargerPageAnim)
        return;

    if (Page_CourseBase_pre_onHandleExtension(_this, &_this->mExtension, event))
        _this->onHandler(event);

    Page_CourseBase_onHandleExtension(_this, &_this->mExtension, event);
}

extern "C" void hook_Page_CourseWiFi_onHandler(ui::Page_CourseWiFi_Ext* _this, ui::UIEvent& event) {
    if (_this->mExtension.mIsInChargerPageAnim)
        return;

    if (Page_CourseBase_pre_onHandleExtension(_this, &_this->mExtension, event))
        _this->onHandler(event);

    Page_CourseBase_onHandleExtension(_this, &_this->mExtension, event);
}

/* --------------------------------------------------------------------- */

extern "C" void hook_ui_Page_CourseGP_onCalc(ui::Page_CourseGP_Ext* _this) {
    _this->onCalc();
    _this->animators[1]->stop(0, 1.0f); // disable trophy on GP menu until i found out why yellow screen
    Page_CourseBase_onCalcExtension(_this);
}

extern "C" void hook_ui_Page_CourseVS_onCalc(ui::Page_CourseVS_Ext* _this) {
    _this->onCalc();
    Page_CourseBase_onCalcExtension(_this);
}

extern "C" void hook_ui_Page_CourseWiFi_onCalc(ui::Page_CourseWiFi_Ext* _this) {
    _this->onCalc();
    Page_CourseBase_onCalcExtension(_this);
}

/* --------------------------------------------------------------------- */

extern "C" void hook_Page_CourseGP_toOut(ui::Page_CourseGP_Ext* _this) {
    _this->toOut();
    Page_CourseBase_toOutExtension(_this);
}

extern "C" void hook_Page_CourseVS_toOut(ui::Page_CourseVS_Ext* _this) {
    _this->toOut();
    Page_CourseBase_toOutExtension(_this);
}

extern "C" void hook_Page_CourseWiFi_toOut(ui::Page_CourseWiFi_Ext* _this) {
    _this->toOut();
    Page_CourseBase_toOutExtension(_this);
}

/* --------------------------------------------------------------------- */

extern "C" void hook_Page_CourseGP_toIn(ui::Page_CourseGP* _this, ui::UIFlow* flow) {
    _this->toIn(flow);
    Page_CourseBase_toInExtension(_this, flow);
}

extern "C" void hook_Page_CourseVS_toIn(ui::Page_CourseVS* _this, ui::UIFlow* flow) {
    _this->toIn(flow);
    Page_CourseBase_toInExtension(_this, flow);
}

extern "C" void hook_Page_CourseWiFi_toIn(ui::Page_CourseWiFi* _this, ui::UIFlow* flow) {
    _this->toIn(flow);
    Page_CourseBase_toInExtension(_this, flow);
}