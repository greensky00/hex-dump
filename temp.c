#include <stdio.h>

#include "hex_dump.h"

void useless_function() {
    (void)print_hex_stream;
    // Do nothing (to check if two different files that include
    // hex_dump.h can be linked well without any conflicts.)
}
