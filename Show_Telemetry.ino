void Show_Telemetry(double timervalue)
{

  if ( millis() > (ST_Savetime + 1000)) {
//    Calculate_Ambient_Lightlevel();

    Serial.println(F("***Serial commands***"));
    Serial.println(F("EST:  move panel East"));
    Serial.println(F("WST:  Move Panel West"));
    Serial.println(F("HLL:  Prep for Hail"));
    Serial.println(F("WND:  Prep for Wind"));
    Serial.println(F("S:  Stop Panel Action"));
    Serial.println(F("T:  Start Tracking"));
    Serial.println(F("*********************"));
    Serial.println(F(""));



    Serial.print(F("East Sensor:"));
    Serial.println(ALE);
    Serial.print(F("West Sensor:"));
    Serial.println(ALW);
    Serial.print(F("Sun location.................:"));
    Serial.println(PR);
    Serial.print(F("aim: "));
    Serial.println(aim);
    Serial.print(F("AmbientLight:"));
    Serial.println(Ambient_Light);
    Serial.print(F("Status:"));
    Serial.println(Status);
    Serial.print(F("Tracking:"));
    Serial.println(Tracking);
    Serial.print(F("Timer:"));
    if (timervalue > 0) {
      Serial.println(timervalue);
      timervalueold = timervalue;
    } else {
      Serial.println(timervalueold);
    }

    Serial.println(F(" "));

    mySerial.print(F("<"));
//	mySerial.println(F("EEPROM"));
    mySerial.print(F("West:"));
    mySerial.print(ALW);	
	mySerial.print(F("           East: "));
	mySerial.println(ALE);

    mySerial.print(F("Sun location:"));
    mySerial.print(PR); 
	mySerial.print(F("     aim: "));
	mySerial.println(aim);
    mySerial.print(F("AmbientLight:"));
    mySerial.println(Ambient_Light);
    mySerial.print(F("Status:"));
    mySerial.println(Status);
    mySerial.print(F("Tracking:"));
    mySerial.println(Tracking);
    mySerial.print(F("Timer:"));
    if (timervalue > 0) {
      mySerial.println(timervalue);
      timervalueold = timervalue;
    } else {
      mySerial.println(timervalueold);
    }

    mySerial.print(F(">"));

    ST_Savetime = millis();
  }
}

