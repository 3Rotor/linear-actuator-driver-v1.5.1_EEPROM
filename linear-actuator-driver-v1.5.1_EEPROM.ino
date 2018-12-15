//  The FUCK ESKOM Project.
//  For controlling a 12v DC driven Chinesium Linear actuator with no positional feedback.
//  Solar location input can be used for precise tracking.
//  Bluetooth connectivity to Android devices for remote control..

#include <Wire.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include "vars.h"
#include "Read_Sensors.h"
#include "Parse_Input.h"
#include "FullStop.h"
#include "Hail_Prep.h"
#include "Wind_Prep.h"
#include "Tracking.h"
#include "Show_Telemetry.h"
#include "comms.h"

SoftwareSerial mySerial(5, 2); // RX, TX
bool debug = false;

void(*resetFunc) (void) = 0; //declare reset function @ address 0

/*
   _____        _
  /  ___|      | |
  \ `--.   ___ | |_  _   _  _ __
   `--. \ / _ \| __|| | | || '_ \
  /\__/ /|  __/| |_ | |_| || |_) |
  \____/  \___| \__| \__,_|| .__/
						   | |
						   |_|
*/
void setup()
{



	Serial.begin(115200); // Start serial communication with Arduino
	mySerial.begin(19200); // Start serial communication with Bluetooth module

	// Write ID to EEPROM
	int sID = 1;

	//   EEPROM.write(1022, sID);

 //read it back
 //EEPROM Address 1022 holds the Arduino number for the PV Panel it is controlling

	sID = EEPROM.read(1022);



	time2run = EEPROMReadlong(20);
	waittime = EEPROMReadlong(24);
	directsunlight = EEPROMReadlong(28);
	daylightlevel = EEPROMReadlong(32);
	target_width = EEPROMReadlong(36);
	aim = EEPROMReadlong(40);


	//Set output pins
	pinMode(Relay1, OUTPUT); // Set pin 7 as OUTPUT
	pinMode(Relay2, OUTPUT); // Set pin 4 as OUTPUT


	//Blank out arrays.
	for (int i = 0; i < LZ_AC; i++) {
		LZ_readings[i] = 0;
	}
	for (int i = 0; i < ALE_AC; i++) {
		ALE_readings[i] = 0;
	}
	for (int i = 0; i < ALW_AC; i++) {
		ALW_readings[i] = 0;
	}
	for (int i = 0; i < 50; i++) {
		//    Calculate_Ambient_Lightlevel();
		Read_Sensors();   Show_Telemetry(0);
		delay(5);
	}


}
/*
  LLLLLLLLLLL                  OOOOOOOOO          OOOOOOOOO     PPPPPPPPPPPPPPPPP
  L:::::::::L                OO:::::::::OO      OO:::::::::OO   P::::::::::::::::P
  L:::::::::L              OO:::::::::::::OO  OO:::::::::::::OO P::::::PPPPPP:::::P
  LL:::::::LL             O:::::::OOO:::::::OO:::::::OOO:::::::OPP:::::P     P:::::P
	L:::::L               O::::::O   O::::::OO::::::O   O::::::O  P::::P     P:::::P
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P::::P     P:::::P
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P::::PPPPPP:::::P
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P:::::::::::::PP
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P::::PPPPPPPPP
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P::::P
	L:::::L               O:::::O     O:::::OO:::::O     O:::::O  P::::P
	L:::::L         LLLLLLO::::::O   O::::::OO::::::O   O::::::O  P::::P
  LL:::::::LLLLLLLLL:::::LO:::::::OOO:::::::OO:::::::OOO:::::::OPP::::::PP
  L::::::::::::::::::::::L OO:::::::::::::OO  OO:::::::::::::OO P::::::::P
  L::::::::::::::::::::::L   OO:::::::::OO      OO:::::::::OO   P::::::::P
  LLLLLLLLLLLLLLLLLLLLLLLL     OOOOOOOOO          OOOOOOOOO     PPPPPPPPPP

*/

void loop() {
	if (millis() > 1200000) {
		Serial.print("resetting ............");
			delay(1000);
		resetFunc(); }

	comms();

	/*
	   once the day is done, move the panels in a horisontal position for the night
	   then leave the system in night time mode.
	*/
	if ((Status == "daylight") || (Status == "start"))
	{
		if (Ambient_Light < 250) {
			Status = "Nighttime-Prepping";
			Tracking = false;
			long ttt = millis();
			long ST_Savetime = millis();
			Track_East();
			while (millis() < ttt + time2run) {
				Read_Sensors();
				if (millis() > (ST_Savetime + 5000)) {
					ST_Savetime = millis();
					Serial.print(F(" Prepping for nighttime. : "));
					Serial.println(ttt + time2run - millis());



				}
				comms();
				if (Status == "prepped") break;
				Show_Telemetry(ttt + time2run - millis());
			}
			FullStop();
			//go horisontal
			Status = "Nighttime-Prepping. Going flat.";
			Tracking = false;
			Track_West();
			ttt = millis();
			ST_Savetime = millis();
			while (millis() < (ttt + (0.55 * time2run))) {
				Read_Sensors();
				if (millis() > (ST_Savetime + 5000)) {
					ST_Savetime = millis();
					Serial.print(F(" Prepping for nighttime. : "));

					Serial.println(ttt + (0.55 * time2run) - millis());
				}
				comms();
				if (Status == "prepped") break;
				Show_Telemetry(ttt + (0.55 * time2run) - millis());
			}
			FullStop(); 
			Status = "Nighttime";
			Tracking = false;
		}
	}


	/*
	   since the system is in nighttime mode,  the panel should be horisontal
	   as it is getting light again once ambient light levels go above 850
	   move the panel over all the way to the east side.
	*/


	if ((Status == "Nighttime")) {

		if (Ambient_Light > 350) {
			Status = "Going East for first-light ";
			Tracking = false;
			Track_East();

			long ttt = millis();
			long ST_Savetime = millis();

			while (millis() < ttt + time2run) {
				Read_Sensors();
				if (millis() > (ST_Savetime + 5000)) {
					ST_Savetime = millis();
					Serial.print(F(" Prepping for morning startup : "));
					Serial.println(ttt + time2run - millis());
				}
				comms();
				if (Status == "prepped") break;
				Show_Telemetry(ttt + time2run - millis());
			}
			Status = "prepped";
			Tracking = false;
			FullStop();
		}
	}


	if ((Ambient_Light > daylightlevel) && (Status != "daylight") && (Status != "Hail") && (Status != "Wind"))
	{
		//    if ((Ambient_Light > 800))


		if (Status != "daylight") {
			Status = "daylight";
			Tracking = true;
		}

	}
	if ((Tracking) && (Status == "daylight")) { // to get some bounce out of the clouds moving in

		if ((ALW > directsunlight) || (ALE > directsunlight))
		{
			Track_The_Sun();

		}
		else
		{
			Time_Track();

		}
	}
	Read_Sensors();
	Show_Telemetry(0);
}

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWritelong(int address, long value)
{
	//Decomposition from a long to 4 bytes by using bitshift.
	//One = Most significant -> Four = Least significant byte
	byte four = (value & 0xFF);
	byte three = ((value >> 8) & 0xFF);
	byte two = ((value >> 16) & 0xFF);
	byte one = ((value >> 24) & 0xFF);

	//Write the 4 bytes into the eeprom memory, only if it changed.
	if (EEPROM.read(address) != four) {
		EEPROM.write(address, four);
		Serial.println(F("wrote four"));
	}
	if (EEPROM.read(address + 1) != three) {
		EEPROM.write(address + 1, three);
		Serial.println(F("wrote three"));
	}
	if (EEPROM.read(address + 2) != two) {
		EEPROM.write(address + 2, two);
		Serial.println(F("wrote two"));
	}
	if (EEPROM.read(address + 3) != one) {
		EEPROM.write(address + 3, one);
		Serial.println(F("wrote one"));
	}
}


//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to address + 3.
long EEPROMReadlong(long address)
{
	//Read the 4 bytes from the eeprom memory.
	long four = EEPROM.read(address);
	long three = EEPROM.read(address + 1);
	long two = EEPROM.read(address + 2);
	long one = EEPROM.read(address + 3);

	//Return the recomposed long by using bitshift.
	return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);

}

void BurnEEPROM()
{

	Serial.println(F("we are now burning the eeprom:  "));
	mySerial.print(F("<"));
	mySerial.println(F("EEPROM Updating.......>"));

	delay(500);

	EEPROMWritelong(20, time2run);
	EEPROMWritelong(24, waittime);
	EEPROMWritelong(28, directsunlight);
	EEPROMWritelong(32, daylightlevel);
	EEPROMWritelong(36, target_width);
	EEPROMWritelong(40, aim);
	mySerial.print(F("<"));
	mySerial.println(F("Update Complete.......>"));
	delay(1000);


}

void ReturnSettings()
{
	mySerial.print(F("<"));
	mySerial.print(F("SETTINGS:"));
	mySerial.print(EEPROMReadlong(20));
	mySerial.print(F(":"));
	mySerial.print(EEPROMReadlong(24));
	mySerial.print(F(":"));
	mySerial.print(EEPROMReadlong(28));
	mySerial.print(F(":"));
	mySerial.print(EEPROMReadlong(32));
	mySerial.print(F(":"));
	mySerial.print(EEPROMReadlong(36));
	mySerial.print(F(":"));
	mySerial.print(EEPROMReadlong(40));  //aim
	mySerial.print(F(">"));
	delay(40);

}