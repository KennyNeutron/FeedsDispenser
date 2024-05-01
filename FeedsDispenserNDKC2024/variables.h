bool century = false;
bool h12Flag;
bool pmFlag;

uint8_t Hour = 1;
uint8_t Minute = 2;
uint8_t Second = 3;

uint16_t currentScreen = 0x0000;
bool btn_pressed_toggle = false;

//DISPENSE SETTINGS
bool dispense_unit = false;  //TRUE= Kg    FALSE= g
float toSet_FeedWeight = 0.0;

//FEEDING SCHEDULE
uint8_t FS_StartHour = 0;
uint8_t FS_StartMinute = 0;
uint8_t FS_Repeat = 1;
uint8_t FS_IntervalHour = 1;
uint8_t FS_IntervalMinute = 30;

//Actuators
uint32_t ActuatorRetract_last_millis = 0;
bool ActuatorRetract_flag = false;

uint8_t dispenseRepeat = 0;
uint8_t next_FeedingSchedule_Hour = 0;
uint8_t next_FeedingSchedule_Minute = 0;

bool FeedingDone = false;


//LoadCell
const int HX711_dout = 16;  //mcu > HX711 dout pin
const int HX711_sck = 17;   //mcu > HX711 sck pin
float currentWeight=0.0;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_calVal_eepromAdress = 0;
unsigned long t = 0;