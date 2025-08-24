#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>

#define EMU_LOG(msg) printf("%s\n", msg);
#define EMU_ERR(msg) fprintf(stderr, "ERROR: %s\n", msg); \
                     exit(1);

#endif