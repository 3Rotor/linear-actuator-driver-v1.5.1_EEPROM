void Wind_Prep()
{
	if (Status != "Wind") {
		Serial.println(Status);
		Serial.println(F(" Prepping for high Winds."));
		Serial.println(F(" Please strap the Panel down to the base"));
		Serial.println(F(" On all 4 corners."));
		Status = "Wind";
		Tracking = false;
		delay(20);
		long ttt = millis();
		while ((millis() < ttt + time2run)) {
			Serial.print(F(" Prepping for high Winds. : "));
			Serial.println(ttt + time2run - millis());
			while (mySerial.available() > 0) {
				ComsInput = mySerial.readStringUntil(':');
				New_Aim = mySerial.readStringUntil('>').toInt();
				aim = map(New_Aim, 0, 100, -30, 30);
				Parse_Input();
			}
			if (Status == "prepped") break;

			Track_West();
			Show_Telemetry(ttt + time2run - millis());
		}
		delay(20);
		ttt = millis();
		while ((millis() < ttt + (time2run / 2))) {
			Serial.print(F(" Prepping for high Winds. : "));
			Serial.println(ttt + (time2run / 2) - millis());
			while (mySerial.available() > 0) {
				ComsInput = mySerial.readStringUntil(':');
				New_Aim = mySerial.readStringUntil('>').toInt();
				aim = map(New_Aim, 0, 100, -30, 30);
				Parse_Input();
			}
			if (Status == "prepped") break;
			Track_East();
			Show_Telemetry(ttt + (time2run/2) - millis());
		}
		FullStop();
	}
}

