hex-dump
--------
Simple hex dump embedded library


Author
------
Jung-Sang Ahn <jungsang.ahn@gmail.com>


How to use
----------
(see [example.c](https://github.com/greensky00/hex-dump/blob/master/example.c))

Copy ```hex_dump.h``` to your source directory, include it, and call ```print_hex_stream```.


```C
#include "hex_dump.h"

...

void* buffer;
size_t buffer_length;

...

print_hex_stream(stdout, buffer, buffer_length, PRINT_HEX_OPTIONS_INITIALIZER);
```

![alt text](https://github.com/greensky00/hex-dump/blob/master/docs/hex_dump.jpg "Screenshot")
