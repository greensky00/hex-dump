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

    print_hex_stream(stdout, buf + 7, 256, PRINT_HEX_OPTIONS_INITIALIZER);

    // Dummy function call. Don't need to put this in your code.
    useless_function();

    return 0;
}

