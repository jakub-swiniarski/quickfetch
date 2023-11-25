//colors
#define ASCII_COLOR "\033[22;34m"
#define TEXT_COLOR "\033[0m"

//ascii array size
#define HEIGHT 7
#define WIDTH 15

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
static const char LABELS[HEIGHT][15]={
    "IDK ",
    "IDK ",
    "IDK ",
    "IDK ",
    "IDK ",
    "IDK ",
    "Battery: "
};

static const char *BATTERY="/sys/class/power_supply/BAT0/capacity";
