#ifndef _CT_ONLINE_H
#define _CT_ONLINE_H

#include <mk8/ui/Control_WifiCmnButton.h>
#include <mk8/audio/utl/AudioUtil.h>
#include <mk8/net/NetworkTransport_Menu.h>
#include <mk8/net/NetworkEngine.h>
#include <mk8/enl/Framework.h>
#include <mk8/object/ObjectEngineCollection.h>

#include <mk8/ui/Pages/Page_CourseRouletteWiFi.h>
#include <mk8/ui/Deluxe/Page_CourseExt.h>

#include <mk8/nn/pia.h>

#include "message.h"
#include "course_ext.h"
#include "resource_ext.h"

#define CTGP_PIA_STATION_PROTOCOL_VERSION 0x47

extern bool gIsOnlineToggled;

class NetworkData_CTGP {

  public:
    class CTGP_Entry {
      public:
        enl::UniqueID id;
        int pageId;

        CTGP_Entry() {
            id.stationId = 253;
            id.playerId = 0;
            id.unk1 = 0;
            pageId = 0;
        }
    };

    CTGP_Entry players[12];

    static void init(NetworkData_CTGP* data) {
        for (int i = 0; i < 12; i++) {
            data->players[i] = CTGP_Entry();
        }
    }

    void setVotePage(enl::UniqueID const& uniqueId, int pageId) {

        /* If entry already exist, set vote page */
        for (int i = 0; i < 12; i++) {
            if (this->players[i].id.isFullyEqual(uniqueId)) {
                this->players[i].pageId = pageId;
                return;
            }
        }

        /* If entry doesn't exist, alloc one */
        for (int i = 0; i < 12; i++) {
            if (this->players[i].id.stationId == 253) {
                this->players[i].id = uniqueId;
                this->players[i].pageId = pageId;
                return;
            }
        }
    }
};

class NetworkTransporter_CTGP : public enl::ContentTransporterCommon {
  public:
    NetworkData_CTGP staticData;
    uint64_t lastTimeSent;
    int shouldSendCount;

    static const uint8_t ContentID = 5;

    NetworkTransporter_CTGP() {
        this->packetNo = 0;
        this->contentId = ContentID;
        this->isIdleState = false;
        this->needsUpdate = true;
        this->field_20 = 0;
        this->flagCount = 0;
        this->flagBuffer = nullptr;
        this->updateLastTimeSent();
        this->shouldSendCount = 0;

        int num = enl::Framework::sFrameworkInstance->transportManager->getNeededBufferNum();
        this->messageBuffers.allocBuffer(num, nullptr, 4);

        for (int i = 0; i < num; i++) {
            enl::DoubleBuffer* doubleBuf = new enl::DoubleBuffer(2, sizeof(NetworkData_CTGP));
            this->messageBuffers.pushBack(doubleBuf);
        }

        if (num > 0) {
            this->flagCount = num;
            this->flagBuffer = (char*)MEMAllocFromDefaultHeapEx(num, 4);
        }

        for (int i = 0; i < num; i++) {
            this->flagBuffer[i] = 0;
        }
    }

    bool selfHasVoted() {
        enl::UniqueID& selfPeer = enl::Framework::sFrameworkInstance->m_PeerManager->m_SelfPeer;
        for (int i = 0; i < 12; i++) {
            if (this->staticData.players[i].id == selfPeer) {
                return true;
            }
        }
        return false;
    }

    virtual void init() {
        this->resetReceive();
        this->endIdling();
        this->clearAllReceivedData();
        this->postInit_();
    }

    virtual void* getSendBuffer() const {
        return (void*)&this->staticData;
    }

    virtual size_t getSendBufferSize() const {
        return sizeof(NetworkData_CTGP);
    }

    void updateLastTimeSent() {
        this->lastTimeSent = OSGetSystemTime();
    }

    virtual bool isNeedSend() {

        if (!gIsOnlineToggled) {
            return false;
        }

        this->shouldSendCount = (this->shouldSendCount++) % 4;
        if (enl::Framework::sFrameworkInstance->m_PeerManager->getConnectedNum() > 1) {
            if (!this->shouldSendCount) {
                return true;
            }
        }
        return false;
    }

    virtual uint8_t getContentID(void) const {
        return this->contentId;
    }

    virtual int getPacketNo() const {
        return this->packetNo;
    }

    virtual void receiveCommit(signed char const& playerId) {
        enl::DoubleBuffer* buf = this->messageBuffers.at(playerId);
        buf->field_18 = 0;
        buf->currentIndex = (buf->currentIndex + 1) % 2;
    }

    virtual bool onCheckReceive(signed char const& id, uint8_t* data, size_t size) const {
        bool ret = false;
        if (!this->isIdling() && size) {
            ret = this->onCheckReceiveCore_(id, (NetworkData_CTGP*)data, size);
        }
        return ret;
    }

    virtual void onReceived(signed char const& id, uint8_t* data, size_t size) {
        int bufferId = enl::Framework::sFrameworkInstance->m_PeerManager->getBufferIDByAID(id);
        enl::DoubleBuffer* buffer = this->messageBuffers.at(bufferId);
        enl::Buffer* buf = buffer->array.at(buffer->currentIndex);
        buf->set(data, size);
        this->mask |= (1 << id);
        this->onReceivedCore_(id, (NetworkData_CTGP*)buf->data, buf->size);
    }

    virtual void onDisconnectGone(signed char const& id1, signed char const& id2) {
        this->mask &= ~(1 << id1);
        enl::DoubleBuffer* buffer2 = this->messageBuffers.at(id2);
        buffer2->currentIndex = 0;
        int index = buffer2->currentIndex;

        enl::Buffer* buf = buffer2->array.at(index);
        buf->clear();

        int idx = (buffer2->currentIndex + 1) % 2;
        buf = buffer2->array.at(idx);
        buf->clear();
    }

    virtual size_t readySendStream(enl::RamWriteStream& stream) {
        return stream.writeMemBlock(this->getSendData(), this->getSendBufferSize());
    }

    virtual size_t readyReceiveStream(enl::RamReadStream& stream, enl::Buffer* buffer, size_t size) {
        size_t ret = stream.readMemBlock(buffer->data, size);
        buffer->size = ret;
        return ret;
    }

    virtual void resetReceive() {
        this->mask = 0;
    }

    virtual bool checkReceive(signed char const& id) const {
        return (this->mask & (1 << id)) != 0;
    }

    virtual void onConnectInitialize() {
    }

    virtual bool isNeedCheckTwiceReceive() const {
        return true;
    }

    virtual void unk7(signed char const& id);

    virtual uint8_t* unk11() const {
        return (uint8_t*)this->getSendData2();
    }

    virtual uint8_t* getBufferDataPtrByAID(signed char const& id) const {
        enl::PeerManagerCommon* peerMgr = enl::Framework::sFrameworkInstance->m_PeerManager;
        enl::UniqueID uniqueId = peerMgr->getUniqueIDByAID(id);
        if (uniqueId == peerMgr->m_SelfPeer) {
            return this->unk11();
        }

        int bufferId = peerMgr->getBufferIDByAID(id);
        enl::DoubleBuffer* buffer = this->messageBuffers.at(bufferId);
        enl::Buffer* buf = buffer->array.at(buffer->currentIndex);
        return buf->data;
    }

    virtual uint8_t* getBufferDataPtrByUniqueID(enl::UniqueID const& peer) const {
        enl::PeerManagerCommon* peerMgr = enl::Framework::sFrameworkInstance->m_PeerManager;
        if (peer == peerMgr->m_SelfPeer)
            return this->unk11();

        int bufferId = peerMgr->getBufferIDByUniqueID(peer);
        enl::DoubleBuffer* buffer = this->messageBuffers.at(bufferId);
        enl::Buffer* buf = buffer->array.at(buffer->currentIndex);
        return buf->data;
    }

    virtual void clearAllReceivedData() {
        sead::PtrArray<enl::DoubleBuffer>::iterator it = this->messageBuffers.begin();
        for (; it != this->messageBuffers.end(); ++it) {
            enl::DoubleBuffer& buffer = *it;

            int idx = buffer.currentIndex;
            buffer.array.at(idx)->clear();

            idx = (idx + 1) % 2;
            buffer.array.at(idx)->clear();

            buffer.currentIndex = 0;
        }
        this->resetReceive();
    }

    virtual void postInit_() {
        NetworkData_CTGP::init((NetworkData_CTGP*)this->getSendData());
    }

    virtual void onReceivedCore_(signed char const& aid, void* data, size_t size) {

        enl::UniqueID uniqueId = enl::Framework::sFrameworkInstance->m_PeerManager->getUniqueIDByAID(aid);
        NetworkData_CTGP* ctData = (NetworkData_CTGP*)data;
        for (int i = 0; i < 12; i++) {
            NetworkData_CTGP::CTGP_Entry* ent = &ctData->players[i];
            if (ent->id == uniqueId) {
                this->staticData.setVotePage(uniqueId, ent->pageId);
            }
        }
    }

    virtual bool onCheckReceiveCore_(signed char const&, void*, size_t) const {
        return true;
    }

    virtual void* getSendData() const {
        return (void*)&this->staticData;
    }

    virtual void* getSendData2() const {
        return this->getSendData();
    }

    virtual ~NetworkTransporter_CTGP() {
    }

    static NetworkTransporter_CTGP* sInstance;

    static NetworkTransporter_CTGP* getTransporter() {
        return (NetworkTransporter_CTGP*)enl::Framework::sFrameworkInstance->transportManager->getContentTransporter(
            ContentID);
    }
};

#endif