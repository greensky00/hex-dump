/**
 * Copyright (C) 2017-present Jung-Sang Ahn <jungsang.ahn@gmail.com>
 * All rights reserved.
 *
 * Last modification: May 8, 2017.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#define _CLM_GREEN     "\033[32m"
#define _CLM_B_GREEN   "\033[1;32m"
#define _CLM_RED       "\033[31m"
#define _CLM_B_RED     "\033[1;31m"
#define _CLM_BLUE      "\033[34m"
#define _CLM_B_BLUE    "\033[1;34m"
#define _CLM_MAGENTA   "\033[35m"
#define _CLM_B_MAGENTA "\033[1;35m"
#define _CLM_CYAN      "\033[36m"
#define _CLM_END       "\033[0m"

#define _CL_GREEN(str)     _CLM_GREEN   str _CLM_END
#define _CL_RED(str)       _CLM_RED     str _CLM_END
#define _CL_B_RED(str)     _CLM_B_RED   str _CLM_END
#define _CL_B_BLUE(str)    _CLM_B_BLUE  str _CLM_END
#define _CL_MAGENTA(str)   _CLM_MAGENTA str _CLM_END
#define _CL_B_MAGENTA(str) _CLM_MAGENTA str _CLM_END
#define _CL_CYAN(str)      _CLM_CYAN    str _CLM_END

struct print_hex_options {
    int enable_colors;
    int actual_address;
};

void print_hex_stream(FILE *stream,
                      void *buf,
                      uint64_t buflen,
                      int align)
{
    // hex dump
    size_t i, j;
    fprintf(stream, _CL_B_RED("%p") ", %" PRIu64 " (0x%" PRIx64 ") bytes\n",
            buf, buflen, buflen);

    fprintf(stream, "          ");
    for (i=0; i<align; ++i) {
        if (align <= 16) {
            fprintf(stream, _CL_CYAN(" %x "), (int)i);
        } else {
            fprintf(stream, _CL_CYAN("%02x "), (int)i);
        }
        if ((i + 1) % 8 == 0) {
            fprintf(stream, " ");
        }
    }
    fprintf(stream, "\n");

    for (i=0; i<buflen; i+=align) {
        fprintf(stream, _CL_CYAN("   %04x   "), (int)i);

        for (j=i; j<i+align; ++j){
            if (j < buflen) {
                fprintf(stream, _CL_GREEN("%02x "), ((uint8_t*)buf)[j]);
            } else {
                fprintf(stream, "   ");
            }
            if ((j + 1) % 8 == 0) {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, " ");
        for (j=i; j<i+align && j<buflen; ++j){
            // print only readable ascii character
            if (0x20 <= ((char*)buf)[j] && ((char*)buf)[j] <= 0x7d) {
                fprintf(stream, _CL_B_BLUE("%c"), ((char*)buf)[j]);
            } else {
                fprintf(stream, ".");
            }
        }
        fprintf(stream, "\n");
    }
}


