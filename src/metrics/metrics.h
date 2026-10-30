#ifndef METRICS_H
#define METRICS_H

#include <stdint.h>

typedef struct
{
    uint64_t total;
    uint64_t used;
    uint64_t available;
    uint64_t free;
    double usage_percent;
} ResourceMetrics;

#endif