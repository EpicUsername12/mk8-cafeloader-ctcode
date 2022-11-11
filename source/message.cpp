#include "message.h"

MessagePatcher* messagePatcher = nullptr;

const wchar_t* hook_ui_UILoader_findMessage_(ui::UILoader* _this, int id) {

    if (messagePatcher && messagePatcher->keyExists(id)) {
        return messagePatcher->get(id);
    }
    return _this->findMessage_(id);
}

void MessagePatcher::Initialize() {

    if (this->isInitialized)
        return;

    this->AddMessage(SPEEDOMETER_MSG_ID, L"00 km/h");

    wchar_t* ctgpText = L"  Online CTGP: OFF";
    ctgpText[0] = 0xE045;
    this->AddMessage(ONLINE_TOGGLE_MSG_ID, ctgpText);

    this->isInitialized = true;
}

wchar_t* convertToWchar(const char* str) {
    const int len = strlen(str);
    wchar_t* buffer = (wchar_t*)MEMAllocFromDefaultHeap((len + 1) * 2);
    OSBlockSet(buffer, 0, (len + 1) * 2);
    for (int i = 0; i < len; i++) {
        buffer[i] = str[i] & 0xff;
    }
    return buffer;
}

void MessagePatcher::AddMessage(int id, wchar_t* message) {

    size_t len = (wcslen(message) * 2) + 1;
    wchar_t* buffer = (wchar_t*)MEMAllocFromDefaultHeap(len);
    OSBlockSet(buffer, 0, len);
    memcpy(buffer, message, len);

    this->set(id, buffer);
}

void MessagePatcher::AddMessage(int id, char* message) {

    /* Convert (poorly) to wchar */
    wchar_t* converted = convertToWchar(message);
    this->set(id, converted);
}

void MessagePatcher::ModifyMessage(int id, wchar_t* message) {

    if (!messagePatcher->keyExists(id)) {
        return;
    }

    size_t len = (wcslen(message) * 2) + 1;
    wchar_t* buffer = (wchar_t*)MEMAllocFromDefaultHeap(len);
    OSBlockSet(buffer, 0, len);
    memcpy(buffer, message, len);

    int idx = this->findIndex(id);
    MEMFreeToDefaultHeap(this->messages[idx].data);
    this->messages[idx].id = -1;
    this->set(id, buffer);
}
void MessagePatcher::ModifyMessage(int id, char* message) {

    if (!messagePatcher->keyExists(id)) {
        return;
    }

    /* Convert (poorly) to wchar */
    wchar_t* converted = convertToWchar(message);

    int idx = this->findIndex(id);
    MEMFreeToDefaultHeap(this->messages[idx].data);
    this->messages[idx].id = -1;
    this->set(id, converted);
}