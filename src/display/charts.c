#include <stdio.h>
#include "charts.h"
#include "colors.h"

void print_usage_bar(const char *label, double percentage)
{
    const int width = 30;

    if (percentage < 0)
        percentage = 0;

    if (percentage > 100)
        percentage = 100;

    int filled = (int)(percentage * width / 100.0);

    const char *color;

    if (percentage < 70)
        color = COLOR_GREEN;
    else if (percentage < 85)
        color = COLOR_YELLOW;
    else
        color = COLOR_RED;

    printf("  %-6s [", label);

    printf("%s", color);

    for (int i = 0; i < width; i++)
    {
        printf("%s", i < filled ? "▓" : "-");
    }

    printf("%s] %.1f%%\n", COLOR_RESET, percentage);
}