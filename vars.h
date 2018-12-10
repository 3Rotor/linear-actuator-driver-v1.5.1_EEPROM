
const int AC =4; //average count, scope(how many samples)
const int Relay1 = 7; // Set the pin for relay1
const int Relay2 = 4; // Set the pin for relay2
int PR = 0;        //difference between Photoresistor inputs.
long ALE = 0;        //difference between Photoresistor inputs.
long ALW = 0;        //difference between Photoresistor inputs.
int New_Aim = 0; // motor New speed.
unsigned long tttt = millis();
int directsunlight = 950;   //sensor light level at wich it is considered direct clean sunlight
int daylightlevel = 400; //ambient light at wich it is considered daytime
unsigned long waittime = 75000;
int target_width = 50;
int aim = 2;
unsigned long Ambient_Light = 0;
int ii = 0;
String ComsInput;
String Status = "start";
unsigned long ST_Savetime = 0;  // show telemetry savetime
unsigned long CAL_Savetime = 0; // Calculate_Ambient_Lightlevel save time
unsigned long RS_Savetime = 0;// read sensor savetime
double time2run = 70000;
//long AL_Ave[AC]; // this is the rolling array that holds all the readings to be averaged over
//long ALE_Ave[AC]; // this is the rolling array that holds all the readings to be averaged over
//long ALW_Ave[AC]; // this is the rolling array that holds all the readings to be averaged over

bool Tracking = true;
unsigned long timervalueold = 0;
long FirstLight = 0;

const int LZ_AC = 30;
double LZ_readings[LZ_AC];
int LZ_arrayIndex = 0;
double LZ_total = 0;
double Span = 0;

const int ALE_AC = 6;
double ALE_readings[ALE_AC];
int ALE_arrayIndex = 0;
double ALE_total = 0;

const int ALW_AC = 6;
double ALW_readings[ALW_AC];
int ALW_arrayIndex = 0;
double ALW_total = 0;
