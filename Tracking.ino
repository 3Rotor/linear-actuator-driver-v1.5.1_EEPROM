
void Track_West()
{
	delay(100);
	digitalWrite(Relay2, LOW);
	digitalWrite(Relay1, HIGH);
}

void Track_East()
{
	delay(100);
	digitalWrite(Relay1, LOW);
	digitalWrite(Relay2, HIGH);
}

void Track_The_Sun()
{

	if ((PR <= (aim + (target_width * 0.5))) && (PR >= (aim - (target_width * 0.5)))) {

		//we are on target, stop moving.
		FullStop();

	}
	else {

		if (PR >= (aim + (target_width * 0.5))) {
			Track_West();

		}
		if (PR <= (aim - (target_width * 0.5))) {
      if (Allow_Backtrack)Track_East(); 

		}

	}
	Show_Telemetry(0);


}

//get average of the Ambient Light
void Calculate_Ambient_Lightlevel() {




	if (millis() > (CAL_Savetime + 5)) {
		for (int i = 0; i < AC; i++) {
			//      ALE = ALE + ALE_Ave[i];
			//      ALW = ALW + ALW_Ave[i];
		}
		//    ALE = ALE / (AC + 0);
		//    ALW = ALW / (AC + 0);
		//    PR = ALW - ALE;
		Ambient_Light = ALE + ALW;
		CAL_Savetime = millis();
	}
}


/*
  _____  _
  |_   _|(_)
	| |   _  _ __ ___    ___
	| |  | || '_ ` _ \  / _ \
	| |  | || | | | | ||  __/
	\_/  |_||_| |_| |_| \___|


   _____                     _
  |_   _|                   | |
	| |   _ __   __ _   ___ | | __
	| |  | '__| / _` | / __|| |/ /
	| |  | |   | (_| || (__ |   <
	\_/  |_|    \__,_| \___||_|\_\

  
*/
void Time_Track() {
	double Taim = aim + 15; //add to aim more east
	double ttt = (PR - Taim);

	//here we take an average over 30 readings to smooth out the resultant
	//time inteval for each adjustment
	LZ_total = LZ_total - LZ_readings[LZ_arrayIndex];
	LZ_readings[LZ_arrayIndex] = sqrt(pow(ttt, 2)) * 2;
	LZ_total = LZ_total + LZ_readings[LZ_arrayIndex];
	LZ_arrayIndex += 1;

	// At the end of the array (10 items) then start again
	if (LZ_arrayIndex >= LZ_AC)LZ_arrayIndex = 0;
	Span = LZ_total / LZ_AC;





	if (millis() >= tttt + waittime) {
		delay(50);
		if (ttt > 5) {
			Serial.print(F(">>>>>>>>>>>>>>>Tracking West>>>>>>>>>>>>>>>>>>>>>>"));
			Serial.println(Span);
			Track_West(); delay(Span);
			FullStop();
		}
		if (ttt < -5) {
			Serial.print(F(">>>>>>>>>>>>>>>>>Tracking East>>>>>Disabled>>>>>>>"));
			Serial.println(Span);
			if (Allow_Backtrack)Track_East(); 
			delay(Span);
			FullStop();
		}
		tttt = millis();

	}
	FullStop();
	Show_Telemetry(tttt + waittime - millis());

}

