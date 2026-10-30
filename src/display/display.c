#include <stdio.h>
#include "display.h"
#include "charts.h"
#include "colors.h"
#include "../utils/format.h"

void print_separator(const char *label)
{
    if (label != NULL)
    {
        printf("\n");
        printf("==================================================\n");
        printf("  %s\n", label);
        printf("==================================================\n");
    }
    else
    {
        printf("--------------------------------------------------\n");
    }
}

void display_resource_metrics(
    const char *name,
    const ResourceMetrics *metrics)
{
    printf("\n  %s\n", name);

    printf("    Total:      ");
    format_bytes(metrics->total);
    printf("\n");

    printf("    Used:       ");
    format_bytes(metrics->used);
    printf("\n");

    printf("    Available:  ");
    format_bytes(metrics->available);
    printf("\n");

    printf("    Free:       ");
    format_bytes(metrics->free);
    printf("\n");
}

void display_system_health(
    const ResourceMetrics *ram,
    const ResourceMetrics *disk)
{

    print_separator("RESOURCE DETAILS");

    display_resource_metrics("RAM", ram);
    display_resource_metrics("DISK (/)", disk);

    print_separator("SYSTEM HEALTH CHECK");
    printf("\n%sRESOURCES%s\n\n", COLOR_BOLD, COLOR_RESET);

    print_usage_bar("RAM", ram->usage_percent);
    print_usage_bar("DISK", disk->usage_percent);

    print_separator(NULL);
}