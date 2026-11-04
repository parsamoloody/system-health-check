#include <stdio.h>
#include <sys/sysinfo.h>
#include "metrics/cpu.h"
#include "metrics/memory.h"
#include "metrics/disk.h"
#include "display/display.h"

int main(void)
{
    struct sysinfo info;

    ResourceMetrics ram;
    ResourceMetrics disk;
    double cpu_usage;

    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return 1;
    }

    if (get_memory_metrics(&ram) != 0)
        return 1;

    if (get_disk_metrics("/", &disk) != 0)
        return 1;

    if (get_cpu_usage(&cpu_usage) != 0)
        return 1;

    display_system_health(cpu_usage, &ram, &disk);

    return 0;
}