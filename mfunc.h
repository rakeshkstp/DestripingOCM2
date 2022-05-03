
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"                  
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_LMAGENTA   "\033[01;35m"
#define ANSI_COLOR_GOLDEN	"\033[22;33m"

extern float median(float arr[], int n);
extern float mean_col(float x[], int ci,unsigned int mask[]);
extern float mean_img(float x[],unsigned int mask[]);
extern void fgauss(float x[],int len);
extern void ifgauss(float x[],int len);
