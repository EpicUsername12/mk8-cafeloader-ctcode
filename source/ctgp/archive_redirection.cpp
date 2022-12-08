#include "ctgp/archive_redirection.h"

static bool g_IsRedirectionArchiveLoaded = true;

DECLARE_HOOK(uint8_t*, nwlyt_GetResourceSub, nw::lyt::ArcExtractor* pArc, const char* pDir, uint32_t type,
             const char* pName, uint32_t* pOutSize) {

    /* Load CTGP Archive file */
    if (!g_IsRedirectionArchiveLoaded) {

        uint32_t arcSize = 0;
        uint8_t* arcFile = util::fs::LoadFileEx(CTGP_ARCHIVE_PATH, &arcSize, 32);

        uint32_t decompSize = sead::SZSDecompressor::getDecompSize(arcFile);
        uint8_t* decompBuf = new uint8_t[decompSize];
        sead::SZSDecompressor::decomp(decompBuf, decompSize, arcFile, arcSize);

        MEMFreeToDefaultHeap(arcFile);
    }

    sead::FixedSafeString<FS_MAX_LOCALPATH_SIZE> fullResourceName;
    if (pDir[0] != '.' || pDir[1]) {
        fullResourceName.appendWithFormat("%s/", pDir);
    }

    fullResourceName.appendWithFormat("%.*s/", 4, (const char*)&type);
    fullResourceName.appendWithFormat("%s", pName);

    LOG("-> %s\n", fullResourceName.cstr());

    return real_nwlyt_GetResourceSub(pArc, pDir, type, pName, pOutSize);
}