# ZMemory
<center><img width=100% src="https://github.com/acessors/ZMemory/blob/main/logo.png?raw=true"/></center>
ZMemory is a C++ library / template for patching process memory on unix systems (including android). It's inspired by <a href="https://github.com/MJx0/KittyMemory">KittyMemory</a> and works similar, but the main advantage is that ZMemory can write external processes memory using root permission

###  Development progress

- [X] Basic memory process API (find PID, regions, write and read memory)

- [X] Basic offset HEX patches

- [ ] In-memory value search (simple types, byte arrays)

- [ ] Assembly operand search (using <a href= "https://github.com/capstone-engine/capstone">capstone</a> maybe)

- [ ] ARM / ARM64 method hooking (frida-like)

### Usage example
This example patches a method replace values from true to false, example apk from <a href="https://github.com/acessors/Il2Cpp-Exploitation-POC">Il2Cpp Exploitation POC</a> is used.
```c++
#include <unistd.h>
#include "ZMemory.h"
using namespace ZMemory;

int main() {
    pid_t pid;
    long long base;
    while (1) {
         pid = find_pid("com.Acessor.Il2CppPOC");
         if (pid) {
             base = find_library_base(pid, "libil2cpp.so");
             printf("libil2cpp found! Base: %llu\n", base);
             bool result = patch_offset(pid, base+0x524EA4, "00 00 A0 E3 1E FF 2F E1");
             if (result) {
                 printf("Offset patches successfully!\n");
             } else {
                 printf("Patch failed\n");
             }
             return 0;
         }
         sleep(1);
    }
    
}
```
