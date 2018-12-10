//  The FUCK ESKOM Project.
//  For controlling a 12v DC driven Chinesium Linear actuator with no positional feedback.
//  Solar location input can be used for precise tracking.
//  2 Limit Stop inputs  are available.
//  Bluetooth connectivity to Android devices for remote control.

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

SoftwareSerial mySerial(5, 2); // RX, TX

/*  testing git xhanges on desktop side  >>> laptop
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

	//    mic01

	time2run = EEPROMReadlong(20);
	waittime = EEPROMReadlong(24);
	directsunlight = EEPROMReadlong(28);
	daylightlevel = EEPROMReadlong(32);
	target_width = EEPROMReadlong(36);
	aim = EEPROMReadlong(40);




	/*switch (sID) { //load defaults for each individual Arduino as identified by their EEPROM ID
	case 1:
		time2run = 70000;
		waittime = 50000;
		aim = 0;
		directsunlight = 880;
		target_width = 30;
		daylightlevel = 1000;
		break;

	case 2:
		time2run = 75000;
		waittime = 50001;
		directsunlight = 970;
		aim = 25;
		target_width = 3;
		daylightlevel = 1000;
		break;

	case 3:
		time2run = 65432;
		waittime = 54321;
		directsunlight = 890;
		aim = 0;
		target_width = 15;
		daylightlevel = 1234;
		break;

	default:
		time2run = 65432;
		waittime = 50001;
		directsunlight = 990;
		aim = 110;
		target_width = 30;
		daylightlevel = 1000;
		break;


	}


	Serial.print("Arduino ID:  ");
	Serial.println(sID);
	Serial.print("wait time:  ");
	Serial.println(waittime);
	*/

	//  for (int i = 0; i < AC; i++)AL_Ave[i] = 0;
	//  for (int i = 0; i < AC; i++)PR_Ave[i] = 0;
	//  for (int i = 0; i < AC; i++)ALE_Ave[i] = 0;
	//  for (int i = 0; i < AC; i++)ALW_Ave[i] = 0;

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
	//delay(1000);
	while (mySerial.available() > 0) {
		ComsInput = mySerial.readStringUntil(':');
		Serial.print("ComsInput:  ");
		Serial.println(ComsInput);

		if (ComsInput == "WRTSTN")
		{
			time2run = mySerial.readStringUntil(':').toInt();
			waittime = mySerial.readStringUntil(':').toInt();
			directsunlight = mySerial.readStringUntil(':').toInt();
			daylightlevel = mySerial.readStringUntil(':').toInt();
			target_width = mySerial.readStringUntil('>').toInt();


		}
		else
		{
			New_Aim = mySerial.readStringUntil('>').toInt();
			aim = map(New_Aim, 0, 100, -30, 30);
			Serial.print("This is BlueTooth Input:  ");
			Serial.println(ComsInput);
			Serial.print("Speed:  ");
			Serial.println(New_Aim);

			//delay(1500);
		}
		Parse_Input();

	}

	while (Serial.available() > 0) {
		ComsInput = Serial.readStringUntil(':');
		New_Aim = Serial.readStringUntil('~').toInt();
		//    Serial.print("This is USB Input:  ");
		//    Serial.println(ComsInput);
		Parse_Input();
	}

	delay(10);

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
			Track_East();
			// Track_East();
			while (millis() < ttt + time2run) {
				Read_Sensors();
				Serial.print(" Prepping for nighttime. : ");
				Serial.println(ttt + time2run - millis());
				//			while (mySerial.available() > 0) {
				if (mySerial.available() > 0) {
					ComsInput = mySerial.readStringUntil(':');
					New_Aim = mySerial.readStringUntil('>').toInt();
					aim = map(New_Aim, 0, 100, -30, 30);
					Parse_Input();
				}
				if (Status == "prepped") break;
				Show_Telemetry(ttt + time2run - millis());
			}
			FullStop(); FullStop();
			delay(1000);
			//go horisontal
			Status = "Nighttime-Prepping. Going flat.";
			Tracking = false;
			Track_West();
			ttt = millis();
			while (millis() < (ttt + (0.55 * time2run))) {
				Read_Sensors();
				Serial.print(" Prepping for nighttime. : ");

				Serial.println(ttt + (0.55 * time2run) - millis());
				while (mySerial.available() > 0) {
					ComsInput = mySerial.readStringUntil(':');
					New_Aim = mySerial.readStringUntil('>').toInt();
					aim = map(New_Aim, 0, 100, -30, 30);
					Parse_Input();
				}
				if (Status == "prepped") break;
				Show_Telemetry(ttt + (0.55 * time2run) - millis());
			}
			FullStop(); FullStop();
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
			//Track_East();

			long ttt = millis();
			FirstLight = ttt;
			while (millis() < ttt + time2run) {
				Read_Sensors();

				Serial.print(" Prepping for morning startup : ");
				Serial.println(ttt + time2run - millis());
				while (mySerial.available() > 0) {
					ComsInput = mySerial.readStringUntil(':');
					New_Aim = mySerial.readStringUntil('>').toInt();
					aim = map(New_Aim, 0, 100, -30, 30);
					Parse_Input();
				}
				if (Status == "prepped") break;
				Show_Telemetry(ttt + time2run - millis());
			}
			Status = "prepped";
			Tracking = false;
			FullStop();
			//	FullStop();
		}
	}


	if ((Ambient_Light > daylightlevel) && (Status != "daylight") && (Status != "Hail") && (Status != "Wind"))
	{
		//    if ((Ambient_Light > 800))

		FirstLight = -14400000;

		if ((millis() - FirstLight > 14400000) && (Status != "daylight")) {
			Status = "daylight";
			Tracking = true;
		}
		else {
			Show_Telemetry((FirstLight + 14400000 - millis()) / 1000);


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

	//Write the 4 bytes into the eeprom memory.
	if (EEPROM.read(address) != four) {
		EEPROM.write(address, four);
		Serial.println("wrote four");
	}
	if (EEPROM.read(address + 1) != three) {
		EEPROM.write(address + 1, three);
		Serial.println("wrote three");
	}
	if (EEPROM.read(address + 2) != two) {
		EEPROM.write(address + 2, two);
		Serial.println("wrote two");
	}
	if (EEPROM.read(address + 3) != one) {
		EEPROM.write(address + 3, one);
		Serial.println("wrote one");
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

	Serial.print("we are now burning the eeprom:  ");
	mySerial.print("<");
	mySerial.println("EEPROM Updating.......>");

	delay(1000);

	EEPROMWritelong(20, time2run);
	EEPROMWritelong(24, waittime);
	EEPROMWritelong(28, directsunlight);
	EEPROMWritelong(32, daylightlevel);
	EEPROMWritelong(36, target_width);
	EEPROMWritelong(40, aim);
	mySerial.print("<");
	mySerial.println("Update Compleste.......>");
	delay(1000);


}

void ReturnSettings()
{
	/*
	time2run = EEPROMReadlong(20);
	waittime = EEPROMReadlong(24);
	directsunlight = EEPROMReadlong(28);
	daylightlevel = EEPROMReadlong(32);
	target_width = EEPROMReadlong(36);



	Serial.print("time2run:  ");
	Serial.println(time2run);
	Serial.print("waittime:  ");
	Serial.println(waittime);
	Serial.print("directsunlight:  ");
	Serial.println(directsunlight);
	Serial.print("target_width:  ");
	Serial.println(target_width);
	Serial.print("daylightlevel:  ");
	Serial.println(daylightlevel);
	delay(4000);

	*/



	mySerial.print("<");

	mySerial.print("SETTINGS:");
	mySerial.print(EEPROMReadlong(20));
	mySerial.print(":");
	mySerial.print(EEPROMReadlong(24));
	mySerial.print(":");
	mySerial.print(EEPROMReadlong(28));
	mySerial.print(":");
	mySerial.print(EEPROMReadlong(32));
	mySerial.print(":");
	mySerial.print(EEPROMReadlong(36));
	mySerial.print(">");

	delay(4000);


}