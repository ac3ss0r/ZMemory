#include "ZUtils.h"
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

char * b_hex(char * arr, int size) {
    char * result = (char *) malloc(size);
    for (int i = 0; i < size; i++) {
        sprintf(result+(i*3), "%02X ",  arr[i]);
    };
    return result;
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