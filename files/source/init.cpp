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

void* nw_lyt_MultiArcResourceAccessor_LoadResource(nw::lyt::MultiArcResourceAccessor* _this, uint32_t resType,
                                                   char const* resName, size_t* pSize) {

    uint32_t typeS[] = { resType, 0 };
    return _this->GetResource(resType, resName, pSize);
}

extern "C" uint8_t const* hook_sys_ResourceLoader_loadDirect(sys::ResourceLoader* _this,
                                                             sead::SafeString const& filepath,
                                                             sys::ResourceLoader::LoadArg const& loadArgs) {

    return _this->loadDirect(filepath, loadArgs);
}

extern "C" sead::Heap* hook_ui_Heap_Boot_onCreateHeap(ui::Heap_Boot* _this) {
    sead::Heap* ret = sead::ExpHeap::tryCreate((void*)BootHeapData, 0xD49000, "UIHeap_Boot", false);
    LOG("Heap_Boot -> %s 0x%08x 0x%08x\n", ret->getName().cstr(), ret->getSize(), ret->getFreeSize());
    return ret;
}

extern "C" sead::Heap* hook_ui_Heap_MenuSub_onCreateHeap(ui::UIHeap* _this) {
    sead::Heap* ret = sead::ExpHeap::tryCreate((void*)MenuSubHeapData, 0xD79000, "UIHeap_MenuSub", false);
    LOG("Heap_MenuSub -> %s 0x%08x 0x%08x\n", ret->getName().cstr(), ret->getSize(), ret->getFreeSize());
    return ret;
}