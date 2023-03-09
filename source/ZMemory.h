#pragma once

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <vector>
#include <sys/mman.h>

namespace ZMemory {
    
class Region {
  public:
    long long startAddress;
    long long endAddress;
    size_t length;

    char name[256];
    char dev[64];
    char perms[16];

    long long offset; //int protection;
    long inode;

    bool read, write, exec;

    Region() : startAddress(0), endAddress(0), length(0), /* protection(0),*/
               read(false), write(false), exec(false), offset(0), inode(0) {
    }
};

bool patch_offset(pid_t pid, long long addr, char *hex);

bool mem_read(pid_t pid, long long addr, char *buff, int size);

bool mem_write(pid_t pid, long long addr, char *buff, int size);

std::vector<Region> find_regions(pid_t pid, char *name);

std::vector<Region> get_all_regions(pid_t pid);

long long find_library_base(pid_t pid,  char * name);

pid_t find_pid(char *pname);

}