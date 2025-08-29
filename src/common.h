#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

typedef uint8_t  byte;
typedef uint8_t  bool;
typedef uint16_t word;

#define EMU_LOG(...) printf("info: ");\
                     printf(__VA_ARGS__);\
                     printf("\n")

#define GB_LOG_OP(pc, ...) printf("0x%04X : ", pc);\
                           printf(__VA_ARGS__);\
                           printf("\n")

#define EMU_ERR(...) fprintf(stderr, "error: ");\
                     fprintf(stderr, __VA_ARGS__);\
                     fprintf(stderr, "\n")

#endif