//colors
#define ASCII_COLOR "\033[22;34m"
#define TEXT_COLOR "\033[0m"

//ascii array size
#define HEIGHT 7
#define WIDTH 15

//max label and data length
#define MAX 20

static const char ASCII[HEIGHT][WIDTH]={   
    "      /\\      ",
    "     /  \\     ",
    "    /    \\    ",
    "   /      \\   ",
    "  /   ,,   \\  ",
    " /   |  |   \\ ",
    "/_-''    ''-_\\"
};

//system info
static const char LABELS[HEIGHT][MAX]={
    "CPU TEMP: ",
    "IDK ",
    "IDK ",
    "IDK ",
    "IDK ",
    "IDK ",
    "Battery: "
};
static const char* CPU_TEMP="/sys/class/thermal/thermal_zone9/temp"; //find the thermal zone whose type is x86_pkg_temp
static const char *BATTERY="/sys/class/power_supply/BAT0/capacity";
