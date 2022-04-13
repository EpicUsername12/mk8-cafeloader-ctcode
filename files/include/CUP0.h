#ifndef _CUP0_H
#define _CUP0_H

#include <cafe.h>
#include <util/filesystem.h>

#include <mk8/nw/lyt/Texture.h>
#include <mk8/ui/Heaps/Heap_Common.h>

#include <algorithm>
#include <vector>

#include "message.h"

#define CUP0_MAGIC 0x43555030
#define DEFAULT_CUP0_PATH "data.cup0"

class CUP0 {

  public:
    class Cup {
      public:
        int mPageId;
        int mCupId;

        int mNameId;
        int mIconChangeFrame;
        nw::lyt::TextureInfo* mIconTexture;

        int mTrackNameIds[4];
        int mTrackRetroNameIds[4];
        char* mTrackPaths[4];
        nw::lyt::TextureInfo* mTrackTextures[4];

        Cup() {

            this->mPageId = -1;
            this->mCupId = -1;

            this->mNameId = -1;
            this->mIconChangeFrame = -1;
            this->mIconTexture = nullptr;

            for (int i = 0; i < 4; i++) {
                this->mTrackNameIds[i] = -1;
                this->mTrackRetroNameIds[i] = -1;
                this->mTrackPaths[i] = nullptr;
                this->mTrackTextures[i] = nullptr;
            }
        }
    };

  private:
    int mPageNum;
    int mCupCount;
    Cup* mCupList;

  public:
    CUP0(const char* filepath = DEFAULT_CUP0_PATH);

    Cup* getCup(int pageId, int cupId) {
        for (size_t i = 0; i < this->mCupCount; i++) {
            if (this->mCupList[i].mPageId == pageId && this->mCupList[i].mCupId == cupId) {
                return &this->mCupList[i];
            }
        }
        return nullptr;
    }

    int getNumPages() {
        return this->mPageNum;
    }
};

#endif