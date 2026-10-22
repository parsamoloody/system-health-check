#include <stdio.h>
#include <sys/sysinfo.h>

int main(void)
{
    struct sysinfo info;
    if (sysinfo(&info) != 0)
    {
        perror("sysinfo");
        return 1;
    };

    printf("Uptime: %ld seconds\n", info.uptime);
    printf("Total RAM: %ld bytes\n", info.totalram);
    printf("Free RAM: %ld bytes\n", info.freeram);

    return 0;
}