#include <stdio.h>
#include <sys/sysinfo.h>

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
        printf("============= %s ============\n", label);
    }
    else
        printf("=========================\n");
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
    printf(" | %.1f%%",usage_percent);
    printf("\n");
    printf("Available RAM: ");
    format_bytes(available_ram);
    printf("\n");
    print_separator(NULL);
    return 0;
}