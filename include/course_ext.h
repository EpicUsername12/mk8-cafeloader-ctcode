#ifndef _PATCH_COURSE_H
#define _PATCH_COURSE_H

#include "log.h"

#include <mk8/sys/SystemEngine.h>
#include <mk8/nw/lyt/Resource.h>
#include <mk8/nw/lyt/Layout.h>
#include <mk8/ui/Heaps/Heap_Boot.h>
#include <mk8/ui/Deluxe/Page_CourseExt.h>
#include <mk8/ui/Pages/Page_Bg.h>
#include <filedevice/seadFileDeviceMgr.h>

#include <heap/seadHeapMgr.h>
#include <heap/seadExpHeap.h>

#include <mk8/audio/utl/AudioUtil.h>

#include "CUP0.h"

#define NUM_TRACKS 81

extern CUP0* sCup0;
extern char* gTrackPaths[];
extern char* gTrackPathsBackup[NUM_TRACKS];

void Page_CourseBase_changeTrackIcons(ui::Page_CourseBase* page, ui::Page_CourseExt* ext);
void Page_CourseBase_changeCupIcons(ui::Page_CourseBase* _this, ui::Page_CourseExt* ext);

#include "online.h"

#endif // _PATCH_COURSE_H