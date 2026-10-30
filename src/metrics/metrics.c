#include <stdio.h>
#include "metrics.h"

void calculate_usage(ResourceMetrics *metrics)
{
    if (metrics->total == 0)
    {
        metrics->usage_percent = 0;
        return;
    }

    metrics->used = metrics->total - metrics->available;

    metrics->usage_percent =
        ((double)metrics->used / metrics->total) * 100.0;
}