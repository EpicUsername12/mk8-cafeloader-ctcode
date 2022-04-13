#ifndef _UTIL_FS_H
#define _UTIL_FS_H

#include "log.h"
#include <filedevice/seadFileDeviceMgr.h>
#include <heap/seadHeapMgr.h>

#include <cafe.h>

#include <algorithm>

namespace util {
namespace fs {

uint8_t* LoadFile(const char* path, size_t* outSize, size_t align, bool crashOnError = true);
uint8_t* LoadFileEx(const char* path, size_t* outSize, size_t align, bool crashOnError = true);

} // namespace fs
} // namespace util

#endif