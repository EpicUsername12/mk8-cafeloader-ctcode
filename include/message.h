#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <map>

#define MAX_MESSAGE_COUNT 256
#define SPEEDOMETER_MSG_ID 23337
#define ONLINE_TOGGLE_MSG_ID 23338

#include <mk8/ui/UILoader.h>

class MessagePatcher {

    struct Message {
        int id;
        wchar_t* data;

        Message() {
            id = -1;
            data = nullptr;
        }
    };

    const static int numMessage = 256;

    Message messages[numMessage];
    bool isInitialized;

  public:
    MessagePatcher() {
        this->isInitialized = false;
        for (int i = 0; i < numMessage; i++) {
            this->messages[i] = Message();
        }
    }

    void Initialize();

    void AddMessage(int id, wchar_t* message);
    void AddMessage(int id, char* message);

    void ModifyMessage(int id, wchar_t* message);
    void ModifyMessage(int id, char* message);

    bool keyExists(int id) {
        for (int i = 0; i < numMessage; i++) {
            if (messages[i].id == id) {
                return true;
            }
        }
        return false;
    }

    int findIndex(int id) {
        for (int i = 0; i < numMessage; i++) {
            if (messages[i].id == id) {
                return i;
            }
        }
        return -1;
    }

    void set(int id, wchar_t* data) {
        for (int i = 0; i < numMessage; i++) {
            if (messages[i].id == -1) {
                messages[i].id = id;
                messages[i].data = data;
                break;
            }
        }
    }
    const wchar_t* get(int id) {
        for (int i = 0; i < numMessage; i++) {
            if (messages[i].id == id) {
                return messages[i].data;
            }
        }
        return nullptr;
    }
};

extern MessagePatcher* messagePatcher;

#endif