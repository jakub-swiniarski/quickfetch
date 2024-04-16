#define COL_LOGO "\033[36m"
#define COL_TEXT "\033[0m"
#define N_ROWS 7
#define LEN_DATA 24

static const char *LOGO[N_ROWS] = {   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

static const char *LABELS[N_ROWS] = {
    "Kernel: ",
    "Time: ",
    "Uptime: ",
    "CPU temp: ",
    "Memory: ",
    "Disk: ",
    "Battery: "
};

static const char *UPTIME = "/proc/uptime";
static const char *CPU_TEMP = "/sys/class/thermal/thermal_zone0/temp";
static const char *MEMORY = "/proc/meminfo";
static const char *DISK = "/";
static const char *BATTERY = "/sys/class/power_supply/BAT0/capacity";
