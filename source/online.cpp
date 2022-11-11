#include "online.h"

bool gIsOnlineToggled = false;
ui::Control_WifiCmnButton* onlineCtgpToggleBtn = nullptr;

NetworkTransporter_CTGP* NetworkTransporter_CTGP::sInstance = nullptr;

int hook_net_NetworkEngine_registTransporter_(net::NetworkEngine* _this) {

    int ret = _this->registTransporter_();
    NetworkTransporter_CTGP::sInstance = new NetworkTransporter_CTGP();
    enl::Framework::sFrameworkInstance->transportManager->regist(NetworkTransporter_CTGP::sInstance);
    return ret;
}

void hook_ui_Page_WifiTop_onCreate(ui::Page_WifiTop* _this) {

    _this->onCreate();
    if (!onlineCtgpToggleBtn) {
        onlineCtgpToggleBtn = new ui::Control_WifiCmnButton(_this);
    }
    onlineCtgpToggleBtn->field_00 = 4;
    onlineCtgpToggleBtn->field_24 = 3;
    onlineCtgpToggleBtn->inputKey.requiredInput = MK8_INPUT_PLUS;

    _this->createControl_(onlineCtgpToggleBtn, _this->controls.at(0), "L_CTGP_00");
    onlineCtgpToggleBtn->setMessage(ONLINE_TOGGLE_MSG_ID);
}

extern "C" void hook_ui_Page_WifiTop_toIn(ui::Page_WifiTop* _this, ui::UIFlow* flow) {

    _this->toIn(flow);
    if (!gIsOnlineToggled) {
        ui::UIPageManager* pageMgr = ui::UIEngine::spInstance->pageManager;
        ui::Page_CourseWiFi* pageWiFi = (ui::Page_CourseWiFi*)pageMgr->getPage(ui::Page_CourseWiFi::ID);
        ui::Page_CourseExt* pageWiFiExt = ui::getPageExtension(pageWiFi);
        pageWiFiExt->mCupPage = 0;
        Page_CourseBase_changeCupIcons(pageWiFi, pageWiFiExt);
        Page_CourseBase_changeTrackIcons(pageWiFi, pageWiFiExt);
    }
}

void hook_Control_WifiCmnButton_onHandler(ui::Control_WifiCmnButton* _this, ui::UIEvent& event) {

    if (onlineCtgpToggleBtn && _this == onlineCtgpToggleBtn) {
        if (event.m_InputValue <= MK8_INPUT_A || event.m_InputValue == MK8_INPUT_PLUS) {

            gIsOnlineToggled = !gIsOnlineToggled;
            wchar_t* ctgpText = L"  Online CTGP: OFF";
            if (gIsOnlineToggled) {
                ctgpText = L"  Online CTGP: ON";
            }
            ctgpText[0] = 0xE045; // (+) sign unicode value for Nintendo font

            messagePatcher->ModifyMessage(ONLINE_TOGGLE_MSG_ID, ctgpText);
            onlineCtgpToggleBtn->setMessage(ONLINE_TOGGLE_MSG_ID);
            audio::utl::startSound2D("SE_SYS_DIALOG_OPEN");

            if (!gIsOnlineToggled) {
                ui::UIPageManager* pageMgr = ui::UIEngine::spInstance->pageManager;
                ui::Page_CourseWiFi* pageWiFi = (ui::Page_CourseWiFi*)pageMgr->getPage(ui::Page_CourseWiFi::ID);
                ui::Page_CourseExt* pageWiFiExt = ui::getPageExtension(pageWiFi);
                pageWiFiExt->mCupPage = 0;
                Page_CourseBase_changeCupIcons(pageWiFi, pageWiFiExt);
                Page_CourseBase_changeTrackIcons(pageWiFi, pageWiFiExt);
            }

            return;
        }
    }

    return _this->onHandlerImpl(event); // non virtual
}

/* Too lazy to look at what it does */
void NetworkTransporter_CTGP::unk7(signed char const& id) {
    int v2;   // r11
    int v3;   // ctr
    int v4;   // r7
    char* v5; // r10
    char* v6;

    v2 = 0;
    v3 = 16;
    do {
        if ((id & (1 << v2)) == 0)
            goto LABEL_13;
        v4 = this->flagCount;
        v5 = this->flagBuffer;
        if (v2 >= v4) {
            v6 = this->flagBuffer;
            if (v2 < v4) {
            LABEL_7:
                if (!v5[v2])
                    goto LABEL_8;
                goto LABEL_10;
            }
        } else {
            v6 = &v5[v2];
            if (v2 < v4)
                goto LABEL_7;
        }
        if (!*v5) {
        LABEL_8:
            *v6 = this->field_20;
            goto LABEL_13;
        }
    LABEL_10:
        if (v2 < v4)
            v5 += v2;
        *v6 = *v5 - 1;
    LABEL_13:
        ++v2;
        --v3;
    } while (v3);
}

int hook_StationProtocol_ParseConnectionRequestCommon(nn::pia::transport::StationProtocol* _this,
                                                      nn::pia::transport::ReceivedMessageAccessor const& message,
                                                      bool isRelay) {

    if (nn::pia::transport::StationManager::s_pInstance->localStation) {
        uint8_t expectedVersion = (gIsOnlineToggled) ? CTGP_PIA_STATION_PROTOCOL_VERSION : 3;
        if (message.data[2] != expectedVersion)
            return _this->SendDenyingConnectionResponse(message.stationAddress, 2);

        // Fix the version
        message.data[2] = 3;
        return _this->ParseConnectionRequestCommon(message, isRelay);
    }
    return (int)_this;
}

const int hook_StationProtocol_MakeConnectionRequestData(nn::pia::transport::StationProtocol* _this,
                                                         uint8_t* outputData, uint8_t sendingConnId, bool isRelay,
                                                         bool isInverse) {

    /*
        https://github.com/kinnay/NintendoClients/wiki/Station-Protocol#connection-request
     */

    uint8_t messageType = 1; // Station Protocol -> Connection request
    if (isRelay)
        messageType = 6; // Station Protocol -> Relay connection request

    outputData[0] = messageType;   // Connection Request -> Message type (1 or 6)
    outputData[3] = isInverse;     // Connection Request -> Is inverse connection request
    outputData[2] = 3;             // Connection Request -> Version
    outputData[1] = sendingConnId; // Connection Request -> Connection id

    /* Our little intrusion */
    if (gIsOnlineToggled) {
        outputData[2] = CTGP_PIA_STATION_PROTOCOL_VERSION; // Connection Request -> Version
    }

    uint32_t v11;
    size_t dataSize = _this->GetConnectionRequestDataSize();
    return nn::pia::transport::StationConnectionInfoTable::s_pInstance->localConnInfo.Serialize(outputData + 4, &v11,
                                                                                                dataSize - 4);
}

extern "C" int hook_net_NetworkTransporter_Menu_getVoteResultIndex(net::NetworkTransporter_Menu* _this) {

    int votedIdx = _this->getVoteResultIndex();
    enl::UniqueID& votedPeer = _this->getMenuData()->m_CourseChoice.m_UniqueID;

    for (int i = 0; i < 12; i++) {
        NetworkData_CTGP::CTGP_Entry* ent = &NetworkTransporter_CTGP::sInstance->staticData.players[i];
        if (votedIdx >= 0) {
            if (ent->id == votedPeer) {
                LOG(CONSOLE_ID " Setting page %d from vote!\n", ent->pageId);
                ui::UIPageManager* pageMgr = ui::UIEngine::spInstance->pageManager;
                ui::Page_CourseWiFi* pageWiFi = (ui::Page_CourseWiFi*)pageMgr->getPage(ui::Page_CourseWiFi::ID);
                ui::Page_CourseExt* pageWiFiExt = ui::getPageExtension(pageWiFi);
                pageWiFiExt->mCupPage = ent->pageId;
                Page_CourseBase_changeCupIcons(pageWiFi, pageWiFiExt);
                Page_CourseBase_changeTrackIcons(pageWiFi, pageWiFiExt);

                int choiceTrackId = _this->getMenuData()->m_CourseChoice.m_CourseId >> 1;
                int choiceCupId = 0;
                ui::UICourseList* list = &ui::Heap_Common::getHeap()->courseData->courseList;
                for (int cupId = 0; cupId < 12; cupId++) {
                    for (int trackId = 0; trackId < 4; trackId++) {
                        if (list->cups[cupId].courses[trackId].id == choiceTrackId) {
                            choiceCupId = cupId;
                            break;
                        }
                    }
                }

                gTrackPaths[choiceTrackId] = gTrackPathsBackup[choiceTrackId];
                CUP0::Cup* ctCup = sCup0->getCup(ent->pageId, choiceCupId);
                if (ctCup) {
                    gTrackPaths[choiceTrackId] = ctCup->mTrackPaths[0];
                }
            }
        }
    }
    return votedIdx;
}