void Show_Telemetry(double timervalue)
{

  if ( millis() > (ST_Savetime + 750)) {
//    Pulse indicator, this will flash the P13 LED to indicate life.
	  if (digitalRead(13)) {
		  digitalWrite(13, LOW); 
	  }
	  else {
		  digitalWrite(13, HIGH); 
	  }

	  if (debug) {
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
		  Serial.print(Ambient_Light);
		  Serial.print(F("  EA:")); Serial.println(East_active);


		  Serial.print(F("Status:"));
		  Serial.print(Status);
		  Serial.print(F(" WA:")); Serial.println(West_active);
		  Serial.print(F("Tracking:"));
		  Serial.println(Tracking);
		  Serial.print(F("Timer:"));
		  if (timervalue > 0) {
			  Serial.println(timervalue);
			  timervalueold = timervalue;
		  }
		  else {
			  Serial.println(millis());
		  }

		  Serial.println(F(" "));
	  }

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
    mySerial.print(Ambient_Light);
	mySerial.print(F(" EA:")); mySerial.println(East_active);
    mySerial.print(F("Status:"));
    mySerial.print(Status);
	mySerial.print(F(" WA:")); mySerial.println(West_active);
    mySerial.print(F("Tracking:"));
    mySerial.print(Tracking); 
	mySerial.print(F("       Target Width:")); 
	mySerial.println(target_width); 
    
	mySerial.print(F("Timer:")); 



    if (timervalue > 0) {
      mySerial.print(timervalue);
      timervalueold = timervalue;
    } else {
      mySerial.print(millis());
    }

	mySerial.print(F("       RAM: "));          // F() macro frees up 4 bytes of RAM
	mySerial.println(2048 - freeRam());

    mySerial.print(F(">"));

    ST_Savetime = millis();
  }
 
}

