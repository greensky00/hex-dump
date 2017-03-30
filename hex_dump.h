#pragma once

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

void print_hex_stream(FILE *stream,
                      void *buf,
                      uint64_t buflen,
                      int align)
{
    // hex dump
    size_t i, j;
    fprintf(stream, "(hex) 0x%" PRIx64 ", %" PRIu64 " (0x%" PRIu64 ") bytes\n",
            (uint64_t)buf, buflen, buflen);
    for (i=0; i<buflen; i+=align) {
        fprintf(stream, "   %04x   ", (int)i);
        for (j=i; j<i+align; ++j){
            if (j<buflen) {
                fprintf(stream, "%02x ", ((uint8_t*)buf)[j]);
            } else {
                fprintf(stream, "   ");
            }
            if ((j+1)%8 == 0) {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, " ");
        for (j=i; j<i+align && j<buflen; ++j){
            // print only readable ascii character
            fprintf(stream, "%c",
             (0x20 <= ((char*)buf)[j] && ((char*)buf)[j] <= 0x7d)?
                       ((char*)buf)[j] : '.'  );
        }
        fprintf(stream, "\n");
    }
}


