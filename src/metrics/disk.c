#include <stdio.h>
#include <sys/statvfs.h>
#include "disk.h"

int get_disk_metrics(const char *path, ResourceMetrics *metrics)
{
    struct statvfs st;

    if (statvfs(path, &st) != 0)
    {
        perror("statvfs");
        return -1;
    }

    metrics->total = (uint64_t)st.f_blocks * st.f_frsize;
    metrics->free = (uint64_t)st.f_bfree * st.f_frsize;
    metrics->available = (uint64_t)st.f_bavail * st.f_frsize;

    if (metrics->total == 0)
    {
        fprintf(stderr, "Invalid disk size\n");
        return -1;
    }

    metrics->used = metrics->total - metrics->free;

    metrics->usage_percent =
        ((double)metrics->used / metrics->total) * 100.0;

    return 0;
}