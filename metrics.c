#include <stdio.h>
#include "metrics.h"

void format_bytes(unsigned long bytes)
{
    const char *units[] = {"B", "KiB", "MiB", "GiB", "TiB"};
    double size = bytes;
    int unit = 0;

    while (size >= 1024 && unit < 4)
    {
        size /= 1024;
        unit++;
    }

    printf("%.2f %s", size, units[unit]);
}

void print_separator(const char *label)
{
    if (label)
    {
        printf("================================================================\n\"%s\"\n================================================================\n", label);
    }
    else
        printf("----------------------------------------------------------------\n");
}

unsigned long get_available_ram(void)
{
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL)
    {
        perror("fopen");
        return 0;
    }

    char line[256];
    unsigned long available_kb;

    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "MemAvailable: %lu kB", &available_kb) == 1)
        {
            fclose(file);
            return available_kb * 1024;
        }
    }

    fclose(file);
    return 0;
}