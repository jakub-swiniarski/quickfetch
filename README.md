# QuickFetch - quick system info tool

## Logo
![Logo](logo.png)

## Screenshots
![image](https://github.com/user-attachments/assets/b38c5733-d976-4afe-9aa2-e76290441594)
![image](https://github.com/jakub-swiniarski/quickfetch/assets/77209709/8986e556-c2c4-4f50-b686-5ed4b8da94be)

## How to install?
### Compile & install
Run this with root privileges:
```shell
make install
```

### How to run?
Use this command:
```shell
qf
```

### How to uninstall?
Go inside the cloned repository and run this with root privileges: <br/>
```shell
make uninstall
```

## Configuration
You can configure QuickFetch by editing the source code. 

## How to setup CPU temperature detection?
### Find the CPU thermal zone
```shell
cat /sys/class/thermal/thermal_zone*/type
```
Look for x86_pkg_temp (this is your CPU thermal zone).

### Example
Counting from 0, x86_pkg_temp is 9th on the list. <br>
Edit config.h:
```c
static const char *cpu_temp = "/sys/class/thermal/thermal_zone9/temp";
```
Recompile & reinstall to see the changes.
