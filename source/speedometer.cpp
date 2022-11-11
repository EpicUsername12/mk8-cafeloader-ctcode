#include "speedometer.h"

/* ui::Page_Race timer always appear */
ui::UIControl* pageRaceMainControl = nullptr;

extern "C" void hook_ui_Page_Race_onCreate(ui::Page_Race* _this) {
    _this->onCreate();
    _this->loadTimeControl_(0);
}

extern "C" void hook_ui_Page_Race_bindWindowLayout_(ui::Page_Race* _this, ui::UIControl* mainControl,
                                                    ui::RaceWindow* raceWindow) {

    if (!pageRaceMainControl) {
        pageRaceMainControl = mainControl;
        nw::lyt::Pane* speedoPane = pageRaceMainControl->findPane("L_Speedometer_00");
        if (speedoPane) {
            speedoPane->setVisible(false);
        }
    }
    _this->bindWindowLayout_(mainControl, raceWindow);
}

extern "C" void hook_ui_Page_Race_onCalc(ui::Page_Race* _this) {

    _this->onCalc();

    int idx = 0;
    enl::Framework* framework = enl::Framework::sFrameworkInstance;
    ui::MenuMode gameMode = ui::Heap_Common::getHeap()->courseData->courseRelatedData.selectedMenuMode;

    if (pageRaceMainControl) {

        if ((gameMode == ui::WIFI_SP || gameMode == ui::WIFI_MP) && framework) {
            idx = framework->m_PeerManager->getPlayerIDByUniqueID(framework->m_PeerManager->m_SelfPeer);
        }
        float moveSpeed =
            object::ObjectEngineCollection::spKartDirector->getKartUnit(idx)->vehicle->vehicleMove->driveSpd * 12.0f;

        char buffer[32];
        __os_snprintf(buffer, 32, "%.0f km/h", moveSpeed);
        messagePatcher->ModifyMessage(SPEEDOMETER_MSG_ID, buffer);

        nw::lyt::Pane* speedo = pageRaceMainControl->findPane("L_Speedometer_00");
        if (speedo) {
            speedo->setVisible(true);
            pageRaceMainControl->setMessage(speedo, SPEEDOMETER_MSG_ID);
        }
    }
}