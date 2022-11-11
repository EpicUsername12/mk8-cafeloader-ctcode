#include "resource_ext.h"

/* https://wiki.tockdom.com/wiki/YAZ0_(File_Format) */
void decompress_yaz0(uint8_t* src, uint8_t* src_end, uint8_t* dest, uint8_t* dest_end) {

    u8 group_head = 0;      // group header byte ...
    int group_head_len = 0; // ... and it's length to manage groups

    while (src < src_end && dest < dest_end) {
        if (!group_head_len) {
            //*** start a new data group and read the group header byte.

            group_head = *src++;
            group_head_len = 8;
        }

        group_head_len--;
        if (group_head & 0x80) {
            //*** bit in group header byte is set -> copy 1 byte direct

            *dest++ = *src++;
        } else {
            //*** bit in group header byte is not set -> run length encoding

            // read the first 2 bytes of the chunk
            const u8 b1 = *src++;
            const u8 b2 = *src++;

            // calculate the source position
            const u8* copy_src = dest - ((b1 & 0x0f) << 8 | b2) - 1;

            // calculate the number of bytes to copy.
            int n = b1 >> 4;

            if (!n)
                n = *src++ + 0x12; // N==0 -> read third byte
            else
                n += 2; // add 2 to length

            // a validity check
            /*if (copy_src < szs->data || dest + n > dest_end)
                return ERROR("Corrupted data!\n"); */

            // copy chunk data.
            // don't use memcpy() or memmove() here because
            // they don't work with self referencing chunks.
            while (n-- > 0)
                *dest++ = *copy_src++;
        }

        // shift group header byte
        group_head <<= 1;
    }
}

static uint8_t* sArchiveFile = nullptr;
extern "C" uint8_t const* hook_sys_ResourceLoader_loadDirect(sys::ResourceLoader* _this,
                                                             sead::SafeString const& filepath,
                                                             sys::ResourceLoader::LoadArg const& loadArg) {
    if (!sArchiveFile) {

        sead::FileDevice::LoadArg loadArg;
        loadArg.path = "ui/cmn/ctgp.szs";
        loadArg.alignment = 0x2000;

        sArchiveFile = sead::FileDeviceMgr::instance()->tryLoad(loadArg);
        if (!sArchiveFile) {
            CRASH_ERROR("Couldn't load ui/cmn/ctgp.szs\n");
        }

        Yaz0_Header* yaz0_hdr = reinterpret_cast<Yaz0_Header*>(sArchiveFile);
        uint8_t* yaz0_data_start = sArchiveFile + sizeof(Yaz0_Header);
        uint8_t* yaz0_data_end = sArchiveFile + loadArg.read_size;
        if (yaz0_hdr->magic == 'Yaz0') {
            uint8_t* dest = (uint8_t*)MEMAllocFromDefaultHeapEx(yaz0_hdr->uncompressed_size, 0x2000);
            decompress_yaz0(yaz0_data_start, yaz0_data_end, dest, dest + yaz0_hdr->uncompressed_size);
            delete[] sArchiveFile;
            sArchiveFile = dest;
        } else {
            CRASH_ERROR("Invalid Yaz0 header\n");
        }
    }

    return _this->loadDirect(filepath, loadArg);
}

extern "C" void* hook_nw_lyt_GetResourceSub(nw::lyt::ArcExtractor* archiveEx, const char* dir, uint32_t resType,
                                            const char* resName, uint32_t* pOutSize) {

    if (sArchiveFile) {
        char resTypeName[5];
        memcpy(resTypeName, &resType, sizeof(resType));
        resTypeName[4] = 0;

        char buffer[256];
        if (dir[0] != '.' || dir[1]) {
            __os_snprintf(buffer, 256, "%s/%s/%s", dir, resTypeName, resName);
        } else {
            __os_snprintf(buffer, 256, "%s/%s", resTypeName, resName);
        }

        SARC_Header* header = reinterpret_cast<SARC_Header*>(sArchiveFile);
        SFAT_Header* file_hdr = reinterpret_cast<SFAT_Header*>(sArchiveFile + sizeof(SARC_Header));

        uint32_t hash = 0;
        for (int i = 0; buffer[i] != 0; i++) {
            hash = buffer[i] + hash * file_hdr->hash_key;
        }

        for (uint16_t i = 0; i < file_hdr->node_count; i++) {
            if (file_hdr->entries[i].hash == hash) {
                if (pOutSize) {
                    *pOutSize = file_hdr->entries[i].file_end - file_hdr->entries[i].file_start;
                }
                return reinterpret_cast<void*>(sArchiveFile + header->data_offset + file_hdr->entries[i].file_start);
            }
        }
    }

    return nw::lyt::ArcExtractor::GetResourceSub(archiveEx, dir, resType, resName, pOutSize);
}