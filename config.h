#define COL_LOGO "\033[36m"
#define COL_TEXT "\033[0m"
#define N_ROWS 7
#define LEN_DATA 24

static const char *logo[N_ROWS] = {   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

static const char *labels[N_ROWS] = {
    "Kernel: ",
    "Time: ",
    "Uptime: ",
    "CPU temp: ",
    "Memory: ",
    "Disk: ",
    "Battery: "
};

static const char *uptime = "/proc/uptime";
static const char *cpu_temp = "/sys/class/thermal/thermal_zone0/temp";
static const char *memory = "/proc/meminfo";
static const char *disk = "/";
static const char *battery = "/sys/class/power_supply/BAT0/capacity";
