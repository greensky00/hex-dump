#include <stdio.h>
#include <stdlib.h>

#include "hex_dump.h"

void useless_function();

int main() {
    char buf[1024];
    size_t i;
    for (i=0; i<1024; ++i) {
        buf[i] = rand() % 256;
    }

    struct print_hex_options options = PRINT_HEX_OPTIONS_INITIALIZER;
    print_hex_stream(stdout, buf + 7, 256, options);

    useless_function();

    return 0;
}

