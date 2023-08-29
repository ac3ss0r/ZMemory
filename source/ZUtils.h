#pragma once

#include <stdlib.h>
#include <string.h>
#include "ZDebug.h"

namespace ZUtils {

bool read_file(char *filename, char * buffer, int size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        // this spams alot while scanning pid 
        //LOG("ZMemory: readfile() failed to open file %s\n", filename);
        return false; 
    }
    fgets(buffer, size, file);
    fclose(file);
    return true;
}

void b_hex(char * arr, char * out, int size) {
    for (int i = 0; i < size; i++) {
        sprintf(out+(i*3), "%02X ",  arr[i]);
    };
}

int hex_b(char * hex, char * out) {
    char trimmed[128] = "";
    for (int i = 0; i < strlen(hex); i++) {
        if (hex[i] != ' ')
            strncat(trimmed, &hex[i], 1);
    };
    for (int i = 0; i < strlen(trimmed) / 2; i++) {
        sscanf(trimmed + (i * 2), "%2hhx", out + i);
    }
    return strlen(trimmed) / 2;
}
    
}