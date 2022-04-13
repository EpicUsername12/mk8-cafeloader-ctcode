#include "util/filesystem.h"

uint8_t* util::fs::LoadFile(const char* path, size_t* outSize, size_t align, bool crashOnError) {

    sead::FileDevice::LoadArg loadArg;
    loadArg.path = path;
    loadArg.alignment = align;

    uint8_t* mem = sead::FileDeviceMgr::instance()->tryLoad(loadArg);
    if (!mem && crashOnError) {
        CRASH_ERROR("util::fs::LoadFile(%s) failed!\n"
                    "Couldn't load the file.. Please check your files.",
                    path);
        return nullptr;
    }

    if (outSize) {
        *outSize = loadArg.read_size;
    }

    return mem;
}

uint8_t* util::fs::LoadFileEx(const char* path, size_t* outSize, size_t align, bool crashOnError) {

    sead::FileHandle handle;
    sead::MainFileDevice* fileDevice = sead::FileDeviceMgr::instance()->getMainFileDevice();

    if (!fileDevice->tryOpen(&handle, path, sead::FileDevice::cFileOpenFlag_ReadOnly, 0)) {
        CRASH_ERROR("util::fs::LoadFileEx:open(%s) failed!\n"
                    "Couldn't load the file.. Please check your files.",
                    path);
        return nullptr;
    }

    size_t fsize, rsize;
    if (!fileDevice->tryGetFileSize(&fsize, &handle)) {
        CRASH_ERROR("util::fs::LoadFileEx:size(%s) failed!\n"
                    "Couldn't load the file.. Please check your files.",
                    path);
        return nullptr;
    }

    uint8_t* mem = (uint8_t*)MEMAllocFromDefaultHeapEx(fsize, align);
    if (!fileDevice->tryRead(&rsize, &handle, mem, fsize)) {
        CRASH_ERROR("util::fs::LoadFileEx:read(%s) failed!\n"
                    "Couldn't load the file.. Please check your files.",
                    path);
        MEMFreeToDefaultHeap(mem);
        return nullptr;
    }

    if (!fileDevice->tryClose(&handle)) {
        CRASH_ERROR("util::fs::LoadFileEx:close(%s) failed!\n"
                    "Couldn't load the file.. Please check your files.",
                    path);
        MEMFreeToDefaultHeap(mem);
        return nullptr;
    }

    if (outSize) {
        *outSize = rsize;
    }

    return mem;
}