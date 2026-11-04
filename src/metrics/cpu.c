#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "cpu.h"

static int read_cpu_times(uint64_t *idle, uint64_t *total)
{
    FILE *file = fopen("/proc/stat", "r");

    if (file == NULL)
    {
        perror("fopen /proc/stat");
        return -1;
    }

    unsigned long long user, nice, system, idle_time;
    unsigned long long iowait, irq, softirq, steal;
    int fields = fscanf(
        file,
        "cpu %llu %llu %llu %llu %llu %llu %llu %llu",
        &user, &nice, &system, &idle_time,
        &iowait, &irq, &softirq, &steal);
    fclose(file);

    if (fields != 8)
    {
        fprintf(stderr, "Failed to parse CPU metrics from /proc/stat\n");
        return -1;
    }

    *idle = (uint64_t)(idle_time + iowait);
    *total = (uint64_t)(
        user + nice + system + idle_time + iowait + irq + softirq + steal);
    return 0;
}

int get_cpu_usage(double *usage_percent)
{
    uint64_t idle_before, total_before, idle_after, total_after;

    if (usage_percent == NULL ||
        read_cpu_times(&idle_before, &total_before) != 0)
        return -1;

    sleep(1);

    if (read_cpu_times(&idle_after, &total_after) != 0 ||
        total_after <= total_before)
        return -1;

    uint64_t total_delta = total_after - total_before;
    uint64_t idle_delta = idle_after - idle_before;

    if (idle_delta > total_delta)
        return -1;

    *usage_percent =
        (double)(total_delta - idle_delta) * 100.0 / (double)total_delta;
    return 0;
}