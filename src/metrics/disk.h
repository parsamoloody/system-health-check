#ifndef DISK_H
#define DISK_H

#include "metrics.h"

int get_disk_metrics(const char *path, ResourceMetrics *metrics);

#endif