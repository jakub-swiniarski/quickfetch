#define VERSION "1.0.3"

//colors
#define LOGO_COLOR "\033[22;36m"
#define TEXT_COLOR "\033[0m"

//ascii array size
#define LOGO_HEIGHT 7
#define LOGO_WIDTH 15

//max label and data length
#define MAX 20

static const char LOGO[LOGO_HEIGHT][LOGO_WIDTH]={   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

//system info
static const char LABELS[LOGO_HEIGHT][MAX]={
    "KERNEL: ",
    "UPTIME: ",
    "CPU TEMP: ",
    "RAM: ",
    "DISK: ",
    "BATTERY: ",
    "QF VERSION: "
};
static const char *UPTIME="/proc/uptime";
static const char *CPU_TEMP="/sys/class/thermal/thermal_zone9/temp"; //find the thermal zone whose type is x86_pkg_temp
static const char *MEMORY="/proc/meminfo";
static const char *DISK="/";
static const char *BATTERY="/sys/class/power_supply/BAT0/capacity";
