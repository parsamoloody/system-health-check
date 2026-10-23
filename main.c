#include <stdio.h>
#include <sys/sysinfo.h>
#include "metrics.h"

int main(void)
{
    struct sysinfo info;
    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return 1;
    };

    unsigned long free_ram = info.freeram * info.mem_unit;
    unsigned long total_ram = info.totalram * info.mem_unit;
    unsigned long used_ram = total_ram - free_ram;
    unsigned long available_ram = get_available_ram();
    double usage_percent = ((double)used_ram / total_ram) * 100.0;

    print_separator("System metrics");

    printf("Uptime: %ld seconds\n", info.uptime);
    printf("Total RAM: ");
    format_bytes(total_ram);
    printf("\n");
    printf("Used RAM: ");
    format_bytes(used_ram);
    printf(" | %.1f%%", usage_percent);
    printf("\n");
    printf("Available RAM: ");
    format_bytes(available_ram);
    printf("\n");
    print_separator(NULL);
    return 0;
}