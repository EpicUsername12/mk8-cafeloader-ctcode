#include "init.h"
#include <dynamic_libs/aoc_functions.h>

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
    InitAocFunctionPointers();

    LOG("Hello from playground.\n");
}