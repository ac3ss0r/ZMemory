#include <unistd.h>
#include "include/ZMemory.h"
using namespace ZMemory;

int main() {
    pid_t pid;
    long long base;
    printf("Waiting for target process...\n");
    while (1) {
         pid = find_pid("com.Acessor.Il2CppPOC");
         if (pid) {
             printf("Process found, PID: %d\n", pid);
             base = find_library_base(pid, "libil2cpp.so");
             ZPatch patch = ZPatch(pid, base+0x524EA4, "00 00 A0 E3 1E FF 2F E1");
             if (patch.toggle())  
                  printf("Memory patched sucessfully\n");
             else 
                   printf("Failed to patch PID %d\n", pid);
             return 0;
         }
         sleep(1);
    }
}