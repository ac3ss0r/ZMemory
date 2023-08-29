#pragma once

namespace ZMemory {
class Region {
  public:
	long long startAddress;
	long long endAddress;
	size_t length;

	char name[256];
	char dev[64];
	char perms[16];

	long long offset; 
    //int protection;
	long inode;

	bool read, write, exec;

	Region() : startAddress(0), endAddress(0), length(0), /* protection(0),*/
			   read(false), write(false), exec(false), offset(0), inode(0) {
	}
};
}