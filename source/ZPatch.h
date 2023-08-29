#pragma once

#include <sys/types.h>
#include "ZMemory.h"
#include "ZUtils.h"
#include "ZDebug.h"

namespace ZMemory {
class ZPatch {
  private:
	pid_t pid;
	long long addr;
	int patch_size;
	char orig_data[128];
	char data[128];
	bool state;

  public:
	ZPatch(pid_t pid, long long addr, char *hex) {
		this->pid = pid;
		this->addr = addr;
		this->state = false;
		this->patch_size = ZUtils::hex_b(hex, this->data);
		if (!ZMemory::mem_read(pid, addr, this->orig_data, patch_size)) {
			LOG("ZMemoryPatch: Failed to backup original bytes.\n");
		}
     }

	 bool toggle() {
			state = !state;
			bool success = state ? ZMemory::mem_write(pid, addr, data, patch_size) : ZMemory::mem_write(pid, addr, orig_data, patch_size);
			if (!success)
				LOG("ZMemoryPatch: Failed to perform a patch\n");
			return success;
		}
};
}