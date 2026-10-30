#include <stdio.h>
#include <sys/sysinfo.h>

#include "metrics/memory.h"
#include "metrics/disk.h"
#include "display/display.h"

int main(void)
{
    struct sysinfo info;

    ResourceMetrics ram;
    ResourceMetrics disk;

    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return 1;
    }

    if (get_memory_metrics(&ram) != 0)
        return 1;

    if (get_disk_metrics("/", &disk) != 0)
        return 1;

    // print_separator("SYSTEM INFORMATION");

    // printf("  Uptime: %ld seconds\n", info.uptime);

    display_system_health(&ram, &disk);

    return 0;
}