#ifndef DISPLAY_H
#define DISPLAY_H

#include "../metrics/metrics.h"

void print_separator(const char *label);

void display_resource_metrics(
    const char *name,
    const ResourceMetrics *metrics
);

void display_system_health(
    const ResourceMetrics *ram,
    const ResourceMetrics *disk
);

#endif