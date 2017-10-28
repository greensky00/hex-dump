/**
 * Copyright (C) 2017-present Jung-Sang Ahn <jungsang.ahn@gmail.com>
 * All rights reserved.
 *
 * https://github.com/greensky00
 *
 * Version: 0.1.1
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
#include <string.h>

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
    // If set, print colorful hex dump using ANSI color codes.
    int enable_colors;
    // If set, print actual memory address.
    int actual_address;
    // The number of bytes per line.
    int align;
};

#define PRINT_HEX_OPTIONS_INITIALIZER \
    (struct print_hex_options){1, 1, 16}

static void _print_white_space(FILE* stream,
                               size_t len) {
    for (size_t i=0; i<len; ++i) {
        fprintf(stream, " ");
    }
}

static void __attribute__((unused))
            print_hex_stream(FILE* stream,
                             void* buf,
                             size_t buflen,
                             struct print_hex_options options)
{
    size_t i, j;
    size_t max_addr_len;
    char str_buffer[256];

    // Get the longest address string length
    if (options.actual_address) {
        sprintf(str_buffer, "%p", (char*)buf + buflen);
    } else {
        sprintf(str_buffer, "0x%" PRIx64, buflen);
    }
    max_addr_len = strlen(str_buffer);

    // Header (address, length)
    fprintf(stream,
            (options.enable_colors)
            ? _CL_B_RED("%p") " -- " _CL_B_RED("%p")
            : "%p -- %p",
            buf, (char*)buf + buflen - 1);
    fprintf(stream, ", %" PRIu64 " (0x%" PRIx64 ") bytes\n",
            buflen, buflen);

    // Legend
    _print_white_space(stream, max_addr_len);
    fprintf(stream, "   ");
    for (i = 0; i < (size_t)options.align; ++i) {
        if (options.align <= 16) {
            fprintf(stream,
                    (options.enable_colors)
                    ? _CL_CYAN(" %x ")
                    : " %x ",
                    (int)i);
        } else {
            fprintf(stream,
                    (options.enable_colors)
                    ? _CL_CYAN("%02x ")
                    : "%02x ",
                    (int)i);
        }

        if ((i + 1) % 8 == 0) {
            fprintf(stream, " ");
        }
    }
    fprintf(stream, "\n");

    size_t surplus_bytes = 0;
    uint64_t start_address = (uint64_t)buf;
    if (options.actual_address) {
        // In actual address mode, we do not start from the
        // leftmost spot as address might not be aligned.
        // In this case, calculate the 'surplus_bytes',
        // which denotes the number of bytes to be skipped.
        start_address /= options.align;
        start_address *= options.align;
        surplus_bytes = (uint64_t)buf - start_address;
    }

    for (i = 0; i < buflen + surplus_bytes; i += options.align) {
        // Address
        if (options.actual_address) {
            sprintf(str_buffer, "%p", (char*)start_address + i);
        } else {
            sprintf(str_buffer, "0x%x", (int)i);
        }
        _print_white_space(stream, max_addr_len - strlen(str_buffer));

        fprintf(stream,
                (options.enable_colors)
                ? _CL_CYAN("%s   ")
                : "%s   ",
                str_buffer);

        // Hex part
        for (j = i; j < i+options.align; ++j){
            if (j < buflen + surplus_bytes &&
                start_address + j >= (uint64_t)buf &&
                start_address + j <  (uint64_t)buf + buflen) {
                uint64_t idx = j - surplus_bytes;
                fprintf(stream,
                        (options.enable_colors)
                        ? _CL_GREEN("%02x ")
                        : "%02x ",
                        ((uint8_t*)buf)[idx]);
            } else {
                fprintf(stream, "   ");
            }

            if ((j + 1) % 8 == 0) {
                fprintf(stream, " ");
            }
        }

        // Ascii character part
        fprintf(stream, " ");
        for (j = i; j < i+options.align; ++j){
            if (j < buflen + surplus_bytes &&
                start_address + j >= (uint64_t)buf &&
                start_address + j <  (uint64_t)buf + buflen) {
                uint64_t idx = j - surplus_bytes;

                // print only readable ascii character
                if (0x20 <= ((char*)buf)[idx] && ((char*)buf)[idx] <= 0x7d) {
                    // Printable character
                    fprintf(stream,
                            (options.enable_colors)
                            ? _CL_B_BLUE("%c")
                            : "%c",
                            ((char*)buf)[idx]);
                } else {
                    // Otherwise
                    fprintf(stream, ".");
                }
            } else {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, "\n");
    }
}

