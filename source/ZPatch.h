#include <sys/types.h>

class ZPatch {
private:
    pid_t pid;
    long long addr;
    int patch_size;
    char orig_data[128];
    char data[128];
    bool state;

public:
    ZPatch(pid_t pid, long long addr, char* hex);
    bool toggle();
};