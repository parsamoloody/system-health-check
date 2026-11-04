A Linux system health checker that collects CPU utilization, RAM, and disk usage metrics and evaluates system health based on resource availability and usage. CPU utilization is sampled over a one-second interval.

#### Requirements
- gcc compiler


#### Build
```bash
make
```
#### Run

```bash
make run
```

#### Cleanup and rebuild
```bash
make clean && make
```
### Supported Platforms

- Linux🐧 (Ubuntu, Debian, Arch, Fedora, AlmaLinux, etc.)

![Linux system health check](https://github.com/parsamoloody/parsamoloody/blob/main/assets/image.png?raw=true)