#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint8_t  bool;

#define FPS_CAP 60

#define EMU_LOG(...) printf("info: ");\
                     printf(__VA_ARGS__);\
                     printf("\n")

#define GB_LOG_OP(pc, ...) printf("$%04X : ", pc);\
                           printf(__VA_ARGS__);\
                           printf("\n")

#define EMU_ERR(...) fprintf(stderr, "error: ");\
                     fprintf(stderr, __VA_ARGS__);\
                     fprintf(stderr, "\n");\
                     exit(1)

#endif