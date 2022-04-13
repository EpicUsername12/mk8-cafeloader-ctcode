#include "CUP0.h"

struct CUP0_Header {
    uint32_t magic;
    size_t numCups;
    size_t stringTableOffset;
};

struct CUP0_TrackEntry {
    size_t trackPathOffset;
    size_t trackPicPathOffset;
    size_t trackNameOffset;
    size_t trackRetroOffset;
};

struct CUP0_CupEntry {
    int pageId;
    int cupId;
    size_t cupNameOffset;
    int cupFrameAnim;
    CUP0_TrackEntry tracks[4];
};

CUP0::CUP0(const char* filepath) {

    uint8_t* filedata = util::fs::LoadFileEx(filepath, nullptr, 0x1000);
    CUP0_Header* header = (CUP0_Header*)filedata;
    if (header->magic != CUP0_MAGIC) {
        CRASH_ERROR("[CUP0] The file magic value isn't valid, please check your files.\n");
    }

    this->mCupCount = header->numCups;
    this->mCupList = (CUP0::Cup*)MEMAllocFromDefaultHeapEx(sizeof(CUP0::Cup) * this->mCupCount, 4);
    for (size_t i = 0; i < this->mCupCount; i++) {
        this->mCupList[i] = CUP0::Cup();
    }

    char* stringTable = (char*)filedata + header->stringTableOffset;
    CUP0_CupEntry* cupEntries = (CUP0_CupEntry*)(filedata + sizeof(CUP0_Header));
    for (size_t i = 0; i < this->mCupCount; i++) {
        CUP0::Cup* cup = &this->mCupList[i];

        cup->mPageId = cupEntries[i].pageId;
        cup->mCupId = cupEntries[i].cupId;
        cup->mIconChangeFrame = cupEntries[i].cupFrameAnim;

        char* cupName = &stringTable[cupEntries[i].cupNameOffset];
        messagePatcher->AddMessage(14337 + i, cupName);
        cup->mNameId = 14337 + i;

        for (int j = 0; j < 4; j++) {
            char* trackName = &stringTable[cupEntries[i].tracks[j].trackNameOffset];
            char* trackNameRetro = &stringTable[cupEntries[i].tracks[j].trackRetroOffset];
            char* trackPath = &stringTable[cupEntries[i].tracks[j].trackPathOffset];
            char* trackIconPath = &stringTable[cupEntries[i].tracks[j].trackPicPathOffset];

            cup->mTrackPaths[j] = trackPath;
            messagePatcher->AddMessage(15337 + (i * 4) + j, trackName);
            cup->mTrackNameIds[j] = 15337 + (i * 4) + j;

            if (strlen(trackNameRetro) > 0) {
                messagePatcher->AddMessage(15937 + (i * 4) + j, trackNameRetro);
                cup->mTrackRetroNameIds[j] = 15937 + (i * 4) + j;
            }

            uint32_t outSize = 0;
            uint8_t* trackIcon = util::fs::LoadFileEx(trackIconPath, &outSize, 0x1000);
            cup->mTrackTextures[j] = new nw::lyt::TextureInfo();
            if (!nw::lyt::LoadTexture(cup->mTrackTextures[j], trackIcon, outSize)) {
                CRASH_ERROR("[CUP0] Couldn't load a track icon texture, please check your files.\n");
            }
        }
    }

    this->mPageNum = 0;
    for (size_t i = 0; i < this->mCupCount; i++) {
        if (this->mCupList[i].mPageId > this->mPageNum) {
            this->mPageNum = this->mCupList[i].mPageId;
        }
    }
}