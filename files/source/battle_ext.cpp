#include "battle_ext.h"

ui::Control_NXBtnL* mBtnL = nullptr;
ui::Control_NXBtnR* mBtnR = nullptr;
bool sDeluxeBattleTracks = false;
bool sInSwapAnimation = false;

struct BattleName {
    char* retroName;
    char* trackName;
    const char* picFilepath;
    const char* trackDir;
    nw::lyt::TextureInfo* texture;
};

// clang-format off
static BattleName sBattleCourses[] = {
    { nullptr,  "Battle Stadium",      "custom/cPict_GDx_BtStadium.bflim",         "Gu_BtStadium",         nullptr },
    { nullptr,  "Sweet Sweet Kingdom", "custom/cPict_GDx_BtSweetKingdom.bflim",    "Gu_BtSweet",           nullptr },
    { nullptr,  "Dragon Palace",       "custom/cPict_GDx_BtDragonPalace.bflim",    "Gu_BtDojo",            nullptr },
    { nullptr,  "Lunar Colony",        "custom/cPict_GDx_BtLunarColony.bflim",     "Gu_BtMoon",            nullptr },
    { "3DS",    "Wuhu Town",           "custom/cPict_GDx_BtWuhuTown.bflim",        "Gu_BtWuhuTown",        nullptr },
    { "GCN",    "Luigi's Mansion",     "custom/cPict_GDx_BtLuigiMansion.bflim",    "Gu_BtLuigiMansion",    nullptr },
    { "SNES",   "Battle Course 1",     "custom/cPict_GDx_BtBattleCourse1.bflim",   "Gu_BtBattle1",         nullptr },
    { nullptr,  "Urchin Underpass",    "custom/cPict_GDx_BtUrchin.bflim",          "Gu_BtDekaLine",        nullptr },
};
// clang-format on

extern "C" void hook_Page_CourseBattle_onCreate(ui::Page_CourseBattle* _this) {

    _this->onCreate();

    mBtnL = new ui::Control_NXBtnL(ui::Control_NXBtnL::TEXTURE_L);
    mBtnL->field_00 = 8;
    mBtnR = new ui::Control_NXBtnR(ui::Control_NXBtnR::TEXTURE_R);
    mBtnR->field_00 = 9;

    _this->createControl_(mBtnL, _this->m_BattleCourseBflyt, "L_LBtn_00");
    _this->createControl_(mBtnR, _this->m_BattleCourseBflyt, "L_RBtn_00");

    const int num_bt_ents = sizeof(sBattleCourses) / sizeof(BattleName);
    for (int i = 0; i < num_bt_ents; i++) {

        if (sBattleCourses[i].retroName) {
            messagePatcher->AddMessage(DELUXE_BT_RETRO_ID + i, sBattleCourses[i].retroName);
        }
        messagePatcher->AddMessage(DELUXE_BT_TRACK_ID + i, sBattleCourses[i].trackName);
        LOG("%s %s (%d %d)\n", sBattleCourses[i].retroName, sBattleCourses[i].trackName, DELUXE_BT_RETRO_ID + i,
            DELUXE_BT_TRACK_ID + i);

        size_t size = 0;
        uint8_t* data = util::fs::LoadFile(sBattleCourses[i].picFilepath, &size, 0x1000, true);
        sBattleCourses[i].texture = new nw::lyt::TextureInfo();
        if (!nw::lyt::LoadTexture(sBattleCourses[i].texture, data, size)) {
            CRASH_ERROR("Couldn't load battle picture texture -> %s\n", sBattleCourses[i].picFilepath);
        }
    }

    ui::UIAnimator* AnimatorTrackIO = _this->createAnimator(2, _this->m_BattleCourseBflyt, 2);
    AnimatorTrackIO->bind(0, "TrackIn");
    AnimatorTrackIO->bind(1, "TrackOut");
}

void swapBattleTracks(ui::Page_CourseBattle* _this) {
    if (sDeluxeBattleTracks) {
        for (int i = 0; i < 8; i++) {
            ui::Control_CourseButton* button = _this->m_CourseButtons[i];
            button->setTexture(button->coursePictPane, sBattleCourses[i].texture, 1);
            button->setVisible(button->coursePictPane, 1);
            button->setVisible(button->courseMoviePane, 0);
            button->setMessage(button->courseNameTextPane, DELUXE_BT_TRACK_ID + i);

            int animIdx = button->boolean ? 1 : 3;
            if (sBattleCourses[i].retroName) {
                button->animators[animIdx]->stop(0, 0.0f);
                button->setVisible(button->classicNameTextPane, 1);
                button->setMessage(button->classicNameTextPane, DELUXE_BT_RETRO_ID + i);
            } else {
                button->animators[animIdx]->stop(0, 1.0f);
                button->setVisible(button->classicNameTextPane, 0);
            }
            gTrackPaths[button->courseId] = (char*)sBattleCourses[i].trackDir;
        }
    } else {
        for (int i = 0; i < 8; i++) {
            gTrackPaths[_this->m_CourseButtons[i]->courseId] = gTrackPaths[_this->m_CourseButtons[i]->courseId];
            ui::UICourseList* list = &ui::Heap_Common::getHeap()->courseData->courseList;
            for (int cupIdx = 0; cupIdx < 12; cupIdx++) {
                for (int trackIdx = 0; trackIdx < 8; trackIdx++) {
                    if (list->cups[cupIdx].courses[trackIdx].id == _this->m_CourseButtons[i]->courseId) {
                        _this->m_CourseButtons[i]->setCourse(list->cups[cupIdx].courses[trackIdx], nullptr);
                        break;
                    }
                }
            }
        }
    }
}

extern "C" void hook_Page_CourseBattle_toOut(ui::Page_CourseBattle* _this) {
    _this->toOut();
    if (sDeluxeBattleTracks) {
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
    }
}

extern "C" void hook_Page_CourseBattle_toIn(ui::Page_CourseBattle* _this, ui::UIFlow* flow) {
    _this->toIn(flow);
    swapBattleTracks(_this);
    if (sDeluxeBattleTracks) {
        ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
        ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
    }
}

extern "C" void hook_Page_CourseBattle_onCalc(ui::Page_CourseBattle* _this) {
    if (sInSwapAnimation) {
        // If TrackOut done, and TrackIn ready, do TrackIn
        if (_this->animators[2]->isEnd(1)) {
            sDeluxeBattleTracks = !sDeluxeBattleTracks;
            swapBattleTracks(_this);
            _this->animators[2]->play_(0); // TrackIn
        }

        if (_this->animators[2]->isEnd(0)) {
            sInSwapAnimation = false;
        }
    }
}

extern "C" void hook_Page_CourseBattle_onHandler(ui::Page_CourseBattle* _this, ui::UIEvent& event) {

    if (sInSwapAnimation) {
        return;
    }

    _this->onHandler(event);

    if ((event.m_InputValue == MK8_INPUT_L) || (event.m_InputValue == MK8_INPUT_R)) {
        if (sDeluxeBattleTracks) {
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, -1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        } else {
            ui::Page_Bg::getPage()->animators[6]->setSpeed(0, 1.0f, false);
            ui::Page_Bg::getPage()->animators[6]->play_(0); // BgColor
        }
        _this->animators[2]->play_(1); // TrackOut
        sInSwapAnimation = true;
        audio::utl::startSound2D("SE_SYS_CMN_CURSOR");
    }
}