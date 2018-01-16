Hex Dump
--------
Simple hex dump embedded library


Author
------
Jung-Sang Ahn <jungsang.ahn@gmail.com>


How to use
----------
(see [example.c](https://github.com/greensky00/hex-dump/blob/master/example.c))

Copy ```hex_dump.h``` to your source directory, include it, and call ```print_hex_stream``` or ```print_hex_to_buf```.


```C
#include "hex_dump.h"

...

void* buffer;
size_t buffer_length;

...

print_hex_stream(stdout, buffer, buffer_length, PRINT_HEX_OPTIONS_INITIALIZER);

...

char* output;
size_t output_length;
print_hex_to_buf(&output, &output_length, buffer, buffer_length,
                 PRINT_HEX_OPTIONS_INITIALIZER);
...
free(output);

```

![alt text](https://github.com/greensky00/hex-dump/blob/master/docs/hex_dump.jpg "Screenshot")
