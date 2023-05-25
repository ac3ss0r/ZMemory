#include "ZPatch.h"
#include "ZMemory.h"
#include "ZUtils.h"
#include "ZDebug.h"

ZPatch::ZPatch(pid_t pid, long long addr, char* hex) {
    this->pid = pid;
    this->addr = addr;
    this->state = false;
    this->patch_size = ZUtils::hex_b(hex, this->data);
    if (!ZMemory::mem_read(pid, addr, this->orig_data, patch_size)) {
        LOG("ZMemoryPatch: Failed to backup original bytes.\n");
    }
}

bool ZPatch::toggle() {
    state = !state;
    bool success = state ?
        ZMemory::mem_write(pid, addr, data, patch_size) :
        ZMemory::mem_write(pid, addr, orig_data, patch_size);
    if (!success)
        LOG("ZMemoryPatch: Failed to perform a patch\n");
    return success;
}