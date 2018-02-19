#include "hex_dump.h"

#include <stdio.h>
#include <stdlib.h>

void useless_function();

int main() {
    char buf[1024];
    size_t i;
    for (i=0; i<1024; ++i) {
        buf[i] = rand() % 256;
    }

    struct print_hex_options options = PRINT_HEX_OPTIONS_INITIALIZER;

    {
        // Example 1: simply put hex dump to stdout.
        print_hex_stream(stdout, buf + 7, 256, options);
    }

    {
        // Example 2: put hex dump to the given buffer.
        char* output_buffer;
        size_t output_buffer_len;
        options.enable_colors = 0;
        options.actual_address = 0;

        print_hex_to_buf(&output_buffer, &output_buffer_len, buf + 7, 256, options);

        // Print the result.
        printf("%.*s", (int)output_buffer_len, output_buffer);
        // Should free the buffer.
        free(output_buffer);
    }

    // Dummy function call for testing purpose.
    // Don't need to put this in your code.
    useless_function();

    return 0;
}

