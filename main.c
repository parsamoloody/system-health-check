#include <stdio.h>
#include <sys/sysinfo.h>
#include "metrics.h"
#include <sys/statvfs.h>

int main(void)
{
    struct sysinfo info;
    struct statvfs st;

    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return 1;
    };

    if (statvfs("/", &st) != 0)
    {
        perror("statvfs");
        return 1;
    }

    unsigned long free_ram = info.freeram * info.mem_unit;
    unsigned long total_ram = info.totalram * info.mem_unit;
    unsigned long used_ram = total_ram - free_ram;
    unsigned long available_ram = get_available_ram();
    double usage_percent = ((double)used_ram / total_ram) * 100.0;

    print_separator("System metrics");

    unsigned long long total = (unsigned long long)st.f_blocks * st.f_frsize;

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
    printf("Total disk space: ");
    format_bytes(total);
    printf("\n");
    print_separator(NULL);
    return 0;
}