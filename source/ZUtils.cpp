#include "ZUtils.h"

namespace ZUtils {

char * b_hex(char * arr, int size) {
    char * result = (char *) malloc(size);
    for (int i = 0; i < size; i++) {
        sprintf(result+(i*3), "%02X ",  arr[i]);
    };
    return result;
}

int hex_b(char *hex, char * out) {
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