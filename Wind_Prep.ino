void Wind_Prep()
{
	long ST_Savetime = millis();
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
			if (millis() > (ST_Savetime + 5000)) {
				ST_Savetime = millis();
				Serial.print(F(" Prepping for high Winds. : "));
				Serial.println(ttt + time2run - millis());
			}
			comms();
			if (Status == "prepped") break;

			Track_West();
			Show_Telemetry(ttt + time2run - millis());
		}
		delay(20);
		ttt = millis();
		while ((millis() < ttt + (time2run / 2))) {
			if (millis() > (ST_Savetime + 5000)) {
				ST_Savetime = millis();
				Serial.print(F(" Prepping for high Winds. : "));
				Serial.println(ttt + (time2run / 2) - millis());
			}
			comms();
			if (Status == "prepped") break;
			Track_East();
			Show_Telemetry(ttt + (time2run/2) - millis());
		}
		FullStop();
	}
}

