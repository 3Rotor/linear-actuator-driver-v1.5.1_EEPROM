void Hail_Prep()
{
	long ST_Savetime = millis();
	if (Status !=F("Hail")) {
		Serial.println(F(" Prepping for Hail."));
		Serial.println(F(" Please strap the Panel down to the base"));
		Serial.println(F(" On all 4 corners."));
		Status =F("Hail");
		Tracking = false;
		delay(20);

		long ttt = millis();
		while ((millis() < ttt + time2run)) {
			if (millis() > (ST_Savetime + 5000)) {
				ST_Savetime = millis();
				Serial.print(F(" Prepping for Hail. pulling panel East : "));
				Serial.println(ttt + time2run - millis());
			}
			comms();
			if (Status ==F("prepped")) break;

			Track_East();
			Show_Telemetry(ttt + time2run - millis());

		}
		FullStop();
	}
}

