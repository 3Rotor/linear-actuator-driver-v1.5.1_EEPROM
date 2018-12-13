void Hail_Prep()
{
	if (Status != "Hail") {
		Serial.println(F(" Prepping for Hail."));
		Serial.println(F(" Please strap the Panel down to the base"));
		Serial.println(F(" On all 4 corners."));
		Status = "Hail";
		Tracking = false;
		delay(20);

		long ttt = millis();
		while ((millis() < ttt + time2run)) {
			Serial.print(F(" Prepping for Hail. pulling panel East : "));
			Serial.println(ttt + time2run - millis());
			comms();
			if (Status == "prepped") break;

			Track_East();
			Show_Telemetry(ttt + time2run - millis());

		}
		FullStop();
	}
}

