# QuickFetch - quick system info tool

## Example
![image](https://github.com/jakub-swiniarski/quickfetch/assets/77209709/f63208d4-54b6-4c50-a247-5048ef18d573)

## How to install?
### Compile & install
```shell
git clone https://github.com/jakub-swiniarski/quickfetch.git
cd quickfetch
sudo make install
```

### How to run?
Use this command:
```shell
qf
```

### How to uninstall?
Go inside the cloned repository and run: <br/>
```shell
sudo make clean uninstall
```

## Configuration
You can configure QuickFetch by editing the source code. 

## How to setup CPU temperature detection?
### Find the CPU thermal zone
```shell
cd /sys/class/thermal/
cat thermal_zone*/type
```
Look for x86_pkg_temp (this is your CPU thermal zone).

### Example
Counting from 0, x86_pkg_temp is 9th on the list.
Edit config.h:
```c
static const char *CPU_TEMP="/sys/class/thermal/thermal_zone9/temp";
```
