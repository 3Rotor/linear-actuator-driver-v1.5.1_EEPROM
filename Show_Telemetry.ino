void Show_Telemetry(double timervalue)
{

  if ( millis() > (ST_Savetime + 10)) {
//    Calculate_Ambient_Lightlevel();

    Serial.println("***Serial commands***");
    Serial.println("EST:  move panel East");
    Serial.println("WST:  Move Panel West");
    Serial.println("HLL:  Prep for Hail");
    Serial.println("WND:  Prep for Wind");
    Serial.println("S:  Stop Panel Action");
    Serial.println("T:  Start Tracking");
    Serial.println("*********************");
    Serial.println("");



    Serial.print("East Sensor:");
    Serial.println(ALE);
    Serial.print("West Sensor:");
    Serial.println(ALW);
    Serial.print("Sun location.................:");
    Serial.println(PR);
    Serial.print("aim: ");
    Serial.println(aim);
    Serial.print("AmbientLight:");
    Serial.println(Ambient_Light);
    Serial.print("Status:");
    Serial.println(Status);
    Serial.print("Tracking:");
    Serial.println(Tracking);
    Serial.print("Timer:");
    if (timervalue > 0) {
      Serial.println(timervalue);
      timervalueold = timervalue;
    } else {
      Serial.println(timervalueold);
    }

    Serial.println(" ");

    mySerial.print("<");
    mySerial.print("East Sensor:");
    mySerial.println(ALE);
    mySerial.print("West Sensor:");
    mySerial.println(ALW);
    mySerial.print("Sun location:");
    mySerial.println(PR);
    mySerial.print("AmbientLight:");
    mySerial.println(Ambient_Light);
    mySerial.print("Status:");
    mySerial.println(Status);
    mySerial.print("Tracking:");
    mySerial.println(Tracking);
    mySerial.print("Timer:");
    if (timervalue > 0) {
      mySerial.println(timervalue);
      timervalueold = timervalue;
    } else {
      mySerial.println(timervalueold);
    }

    mySerial.print(">");

    ST_Savetime = millis();
  }
}

