#include "init.h"

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

    int32_t MK8_OSDynLoad_Acquire_LI = MK8_OSDynLoad_Acquire & 0x03FFFFFC;
    int32_t MK8_OSDynLoad_FindExport_LI = MK8_OSDynLoad_FindExport & 0x03FFFFFC;

    // LI is actually signed, check for it ...
    // Page 367 -> https://fail0verflow.com/media/files/ppc_750cl.pdf
    {
        if (MK8_OSDynLoad_Acquire_LI & 0x02000000) {
            MK8_OSDynLoad_Acquire_LI -= 0x04000000;
        }
        if (MK8_OSDynLoad_FindExport_LI & 0x02000000) {
            MK8_OSDynLoad_FindExport_LI -= 0x04000000;
        }
    }

    OS_SPECIFICS->addr_OSDynLoad_Acquire = MK8_OSDynLoad_Acquire_LI;
    OS_SPECIFICS->addr_OSDynLoad_FindExport = MK8_OSDynLoad_FindExport_LI;

    if (!(MK8_OSDynLoad_Acquire & 2))
        OS_SPECIFICS->addr_OSDynLoad_Acquire += (u32)&MK8_OSDynLoad_Acquire;
    if (!(MK8_OSDynLoad_FindExport & 2))
        OS_SPECIFICS->addr_OSDynLoad_FindExport += (u32)&MK8_OSDynLoad_FindExport;

    InitOSFunctionPointers();
    InitGX2FunctionPointers();
    InitACTFunctionPointers();
    InitFSFunctionPointers();
    InitAocFunctionPointers();

    LOG("Hello from playground.\n");
}