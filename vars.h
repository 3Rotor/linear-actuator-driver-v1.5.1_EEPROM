const int AC =3; //average count, scope(how many samples)
const int Relay1 = 7; // Set the pin for relay1
const int Relay2 = 4; // Set the pin for relay2
int PR = 0;        //difference between Photoresistor inputs.
long ALE = 0;        //difference between Photoresistor inputs.
long ALW = 0;        //difference between Photoresistor inputs.
unsigned long tttt = millis();
int directsunlight = 950;   //sensor light level at wich it is considered direct clean sunlight
int daylightlevel = 400; //ambient light at wich it is considered daytime
unsigned long waittime = 75000;
int target_width = 50;
int aim = 2;
unsigned long Ambient_Light = 0;
int ii = 0;
String ComsInput;
String Status ="start";
unsigned long ST_Savetime = 0;  // show telemetry savetime
unsigned long CAL_Savetime = 0; // Calculate_Ambient_Lightlevel save time
unsigned long RS_Savetime = 0;// read sensor savetime
double time2run = 70000;
bool Tracking = true;
unsigned long timervalueold = 0;
const int LZ_AC = AC*3;
double LZ_readings[LZ_AC];
int LZ_arrayIndex = 0;
double LZ_total = 0;
double Span = 0;
const int ALE_AC = AC;
double ALE_readings[ALE_AC];
int ALE_arrayIndex = 0;
double ALE_total = 0;
const int ALW_AC = AC;
double ALW_readings[ALW_AC];
int ALW_arrayIndex = 0;
double ALW_total = 0;
