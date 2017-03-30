#include <stdio.h>

#include "hex_dump.h"

int main() {
    char buf[256];
    size_t i;
    for (i=0; i<256; ++i) {
        buf[i] = i;
    }

    print_hex_stream(stdout, buf, 256, 16);

    return 0;
}

