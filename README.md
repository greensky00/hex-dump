hex-dump
--------
Simple hex dump embedded library


Author
------
Jung-Sang Ahn <jungsang.ahn@gmail.com>


How to use
----------
(refer to ```example.c```)

Copy ```hex_dump.h``` to your source directory, include it, and call ```print_hex_stream```.


```C
#include "hex_dump.h"

...

void* buffer;
size_t buffer_length;

...

struct print_hex_options options = PRINT_HEX_OPTIONS_INITIALIZER;
print_hex_stream(stdout, buffer, buffer_length, options);
```

![alt text](https://github.com/greensky00/hex-dump/blob/master/docs/hex_dump.jpg "Screenshot")
