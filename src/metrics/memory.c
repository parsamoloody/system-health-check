#include <stdio.h>
#include <sys/sysinfo.h>
#include "memory.h"

static uint64_t get_available_ram(void)
{
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL)
    {
        perror("fopen /proc/meminfo");
        return 0;
    }

    char line[256];
    unsigned long available_kb;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "MemAvailable: %lu kB", &available_kb) == 1)
        {
            fclose(file);
            return (uint64_t)available_kb * 1024;
        }
    }

    fclose(file);
    return 0;
}

int get_memory_metrics(ResourceMetrics *metrics)
{
    struct sysinfo info;

    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return -1;
    }

    metrics->total = (uint64_t)info.totalram * info.mem_unit;
    metrics->free = (uint64_t)info.freeram * info.mem_unit;
    metrics->available = get_available_ram();

    if (metrics->available == 0 || metrics->total == 0)
    {
        fprintf(stderr, "Failed to retrieve memory metrics\n");
        return -1;
    }

    metrics->used = metrics->total - metrics->available;

    metrics->usage_percent =
        ((double)metrics->used / metrics->total) * 100.0;

    return 0;
}