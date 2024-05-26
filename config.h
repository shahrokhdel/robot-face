#define XPOS 0
#define YPOS 0
#define DELTAY 2
#define BUZZER 12

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define ImageWidth1  128 
#define ImageHeight1 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal= 265;
int maxVal= 402;
int freq = 1000;      // Starting frequency

unsigned long startTime;           //some global variables available anywhere in the program
unsigned long currentTime;
const unsigned long periodTime = 5000;  //the value is a number of milliseconds

double x;
double y;
double z;
