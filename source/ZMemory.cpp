#include "ZMemory.h"
#include "ZDebug.h"
#include "ZUtils.h"

namespace ZMemory {

/* this doesn't work for large addresses 
int pwrite(long pid, void * addr, void * stringBuf,
                         size_t size) {
  struct iovec local[1];
  struct iovec remote[1];

  local[0].iov_base = stringBuf;
  local[0].iov_len = size;
  remote[0].iov_base = addr;
  remote[0].iov_len = size;

  return process_vm_writev(pid, local, 1, remote, 1, 0);
}*/

/*
bool dump_region(pid_t pid, Region reg, char * path) {
    char buffer[8];
    FILE * fp = fopen(path, "w");
    if (fp == NULL) { // file error
        return false;
    }
    for (int i =0; i < reg.length; i+=sizeof(buffer)) {
      ssize_t s = mem_read(pid, reg.startAddress+i, &buffer, sizeof(buffer));
      printf("%d\n", s);
      fputs(buffer,fp);
    }
     fclose(fp);
     return true;
}*/

bool patch_offset(pid_t pid, long long addr, char *hex) {
    char data[128];
    int size = ZUtils::hex_b(hex, data);
    return mem_write(pid, addr, data, size);
}

bool mem_read(pid_t pid, long long addr, char *buff, int size) {
    char path[64];
    sprintf(path, "/proc/%d/mem", pid);
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        LOG("ZMemory: mem_read() failed to read process %d memory\n", pid);
        return false;
    }
    fseeko64(fp, addr, 0);
    bool ok = fgets(buff, size, fp);
    fclose(fp);
    return ok;
}

bool mem_write(pid_t pid, long long addr, char *buff, int size) {
    char path[64];
    sprintf(path, "/proc/%d/mem", pid);
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        LOG("ZMemory: mem_write() failed to write process %d memory\n", pid);
        return false;
    }
    fseeko64(fp, addr, 0);
    bool ok = fwrite(buff, 1, size, fp) == size;
    fclose(fp);
    return ok;
}

std::vector<Region> find_regions(pid_t pid, char *name) {
    FILE *fp = NULL;
    char line[512];
    char path[64];
    std::vector<Region> regions;
    sprintf(path, "/proc/%d/maps", (int)pid);
    fp = fopen(path, "r");
    if (fp == NULL) {
        LOG("ZMemory: find_regions() failed to open file PID %d\n", pid);
        return regions;
    }
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, name)) {
            Region region;
            sscanf(line, "%llx-%llx %s %llx %s %lu %s",
                   &region.startAddress, &region.endAddress,
                   &region.perms, &region.offset, &region.dev, &region.inode, &region.name);
            region.length = region.endAddress - region.startAddress;
            region.read = (region.perms[0] == 'r');
            region.write = (region.perms[1] == 'w');
            region.exec = (region.perms[2] == 'x');
            regions.push_back(region);
        }
    }
    fclose(fp);
    return regions;
}

std::vector<Region> get_all_regions(pid_t pid) {
    FILE *fp = NULL;
    char line[512];
    char path[64];
    std::vector<Region> regions;
    sprintf(path, "/proc/%d/maps", (int)pid);
    fp = fopen(path, "r");
    if (fp == NULL) {
        LOG("ZMemory: all_regions() failed to open file PID %d\n", pid);
        return regions;
    }
    while (fgets(line, sizeof(line), fp)) {
        Region region;
        char perms[5] = {0}, dev[11] = {0}, name[256] = {0};
        sscanf(line, "%llx-%llx %s %llx %s %lu %s",
               &region.startAddress, &region.endAddress,
               &region.perms, &region.offset, &region.dev, &region.inode, &region.name);
        region.length = region.endAddress - region.startAddress;
        region.read = (perms[0] == 'r');
        region.write = (perms[1] == 'w');
        region.exec = (perms[2] == 'x');
        regions.push_back(region);
    }
    fclose(fp);
    return regions;
}

pid_t find_pid(char *pname) {
    struct dirent *pDirent;
    DIR *pDir = opendir("/proc/");
    if (pDir == NULL) {
        LOG("ZMemory: find_pid() failed to open /proc\n");
        return NULL;
    }
    while ((pDirent = readdir(pDir)) != NULL) {
        char path[64];
        char cmdline[32];
        sprintf(path, "/proc/%s/cmdline", pDirent->d_name);
        ZUtils::read_file(path, cmdline, 32);
        if (strcmp(cmdline, pname) == 0) {
            pid_t pid = (pid_t)atoi(pDirent->d_name);
            closedir(pDir);
            return pid;
        }
    }
    closedir(pDir);
    return 0;
}

long long find_library_base(pid_t pid,  char * name) {
        for (Region region : find_regions(pid, name)) {
            if (region.exec) return region.startAddress;
        }
    return 0;
}
}
