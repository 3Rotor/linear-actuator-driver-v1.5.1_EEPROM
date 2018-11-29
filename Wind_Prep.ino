void Wind_Prep()
{
	if (Status != "Wind") {
		Serial.println(Status);
		Serial.println(" Prepping for high Winds.");
		Serial.println(" Please strap the Panel down to the base");
		Serial.println(" On all 4 corners.");
		Status = "Wind";
		Tracking = false;
		delay(20);
		long ttt = millis();
		while ((millis() < ttt + 95000)) {
			Serial.print(" Prepping for high Winds. : ");
			Serial.println(ttt + 95000 - millis());
			while (mySerial.available() > 0) {
				ComsInput = mySerial.readStringUntil(':');
				New_Aim = mySerial.readStringUntil('>').toInt();
				aim = map(New_Aim, 0, 100, -20, 20);
				Parse_Input();
			}
			if (Status == "prepped") break;

			Track_West();
			Show_Telemetry(ttt + 95000 - millis());
		}
		delay(20);
		ttt = millis();
		while ((millis() < ttt + 45000)) {
			Serial.print(" Prepping for high Winds. : ");
			Serial.println(ttt + 45000 - millis());
			while (mySerial.available() > 0) {
				ComsInput = mySerial.readStringUntil(':');
				New_Aim = mySerial.readStringUntil('>').toInt();
				aim = map(New_Aim, 0, 100, -20, 20);
				Parse_Input();
			}
			if (Status == "prepped") break;
			Track_East();
			Show_Telemetry(ttt + 45000 - millis());
		}
		FullStop();
	}
}

