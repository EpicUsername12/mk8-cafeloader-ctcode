#pragma once

#include <log.h>
#include <types.h>

#include <dynamic_libs/fs_functions.h>
#include <dynamic_libs/gx2_functions.h>
#include <dynamic_libs/mtxVec_functions.h>
#include <dynamic_libs/os_functions.h>

#include <mk8/object/Item/MapObjParameter.h>

#define CRASH_ERROR(FMT, ARGS...)                         \
    LOG(FMT, ##ARGS);                                     \
    __os_snprintf(log_msg, sizeof(log_msg), FMT, ##ARGS); \
    OSFatal(log_msg);

#define NEW_MALLOC(TYPE, ARGS...) (new ((TYPE*)MEMAllocFromDefaultHeapEx(sizeof(TYPE), 4)) TYPE(##ARGS))
#define NEW_MALLOC_ARR(TYPE, N, ARGS...) (new ((TYPE*)MEMAllocFromDefaultHeapEx(sizeof(TYPE) * N, 4)) TYPE[N](##ARGS))