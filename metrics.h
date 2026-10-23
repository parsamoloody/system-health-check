#ifndef METRICS_H
#define METRICS_H

void format_bytes(unsigned long bytes);
void print_separator(const char *label);
unsigned long get_available_ram(void);

#endif