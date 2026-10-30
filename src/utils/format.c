#include <stdio.h>
#include <stdint.h>
#include "format.h"

void format_bytes(uint64_t bytes)
{
    const char *units[] = {
        "B", "KiB", "MiB", "GiB", "TiB"
    };

    double size = (double)bytes;
    int unit = 0;

    while (size >= 1024 && unit < 4)
    {
        size /= 1024;
        unit++;
    }

    printf("%.2f %s", size, units[unit]);
}