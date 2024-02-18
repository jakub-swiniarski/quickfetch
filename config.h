#define LOGO_COLOR "\033[36m"
#define TEXT_COLOR "\033[0m"

#define N_ROWS 7
#define DATA_LENGTH 24

static const char *LOGO[15] = {   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

//system info
static const char *LABELS[N_ROWS] = {
    "KERNEL: ",
    "TIME: ",
    "UPTIME: ",
    "CPU TEMP: ",
    "MEMORY: ",
    "DISK: ",
    "BATTERY: "
};
static const char *UPTIME = "/proc/uptime";
static const char *CPU_TEMP = "/sys/class/thermal/thermal_zone0/temp";
static const char *MEMORY = "/proc/meminfo";
static const char *DISK = "/";
static const char *BATTERY = "/sys/class/power_supply/BAT0/capacity";
