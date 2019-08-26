#define MESSAGE_BUFFER_SIZE          64
#define MSG_SEND_JOYINPUT            0x62   // 'b' in message
#define MSG_SEND_IMU                 0x64   // 'd' in message
#define MSG_SEND_DRONE_IMU           0x66

char msgBuffer[MESSAGE_BUFFER_SIZE]; 
int msgBufferPointer = 0;

byte controller_roll[4];
byte controller_pitch[4];
byte controller_yaw[4];

struct IMU{
    double roll;
    double pitch;
    double yaw;
};

IMU droneIMU;
IMU controllerIMU;

int joyl_sw;
int joyl_x;
int joyl_y;
