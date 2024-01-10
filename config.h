#define VERSION "1.0.10"

#define LOGO_COLOR "\033[36m"
#define TEXT_COLOR "\033[0m"

#define ROWS_MAX 7

#define DATA_LENGTH 20

static const char LOGO[ROWS_MAX][15]={   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

//system info
static const char LABELS[ROWS_MAX][13]={
    "KERNEL: ",
    "UPTIME: ",
    "CPU TEMP: ",
    "MEMORY: ",
    "DISK: ",
    "BATTERY: ",
    "QF VERSION: "
};
static const char *UPTIME="/proc/uptime";
static const char *CPU_TEMP="/sys/class/thermal/thermal_zone0/temp";
static const char *MEMORY="/proc/meminfo";
static const char *DISK="/";
static const char *BATTERY="/sys/class/power_supply/BAT0/capacity";
