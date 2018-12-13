void comms() {
	//delay(1000);
	while (mySerial.available() > 0) {
		ComsInput = mySerial.readStringUntil(':');
		Serial.print(F("ComsInput:  "));
		Serial.println(ComsInput);

		if (ComsInput == "WRTSTN")
		{
			time2run = mySerial.readStringUntil(':').toInt();
			waittime = mySerial.readStringUntil(':').toInt();
			directsunlight = mySerial.readStringUntil(':').toInt();
			daylightlevel = mySerial.readStringUntil(':').toInt();
			target_width = mySerial.readStringUntil(':').toInt();
			aim = mySerial.readStringUntil('>').toInt();

		}
		else
		{/*
			New_Aim = mySerial.readStringUntil('>').toInt();
			aim = map(New_Aim, 0, 100, -30, 30);
			Serial.print(F("This is BlueTooth Input:  "));
			Serial.println(ComsInput);
			Serial.print(F("Speed:  "));
			Serial.println(New_Aim);*/

		}
		Parse_Input();

	}

	while (Serial.available() > 0) {
		ComsInput = Serial.readStringUntil(':');
		//	New_Aim = Serial.readStringUntil('~').toInt();
			//    Serial.print(F("This is USB Input:  "));
			//    Serial.println(ComsInput);
		Parse_Input();
	}


	delay(10);
}