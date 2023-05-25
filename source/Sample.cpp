#include <unistd.h>
#include "ZMemory.h"
#include "ZPatch.h"
using namespace ZMemory;

int main() {
    pid_t pid;
    long long base;
    while (1) {
         pid = find_pid("com.Acessor.Il2CppPOC");
         if (pid) {
             base = find_library_base(pid, "libil2cpp.so");
             ZPatch patch = ZPatch(pid, base+0x524EA4, "00 00 A0 E3 1E FF 2F E1");
             patch.toggle();
             return 0;
         }
         sleep(1);
    }
}