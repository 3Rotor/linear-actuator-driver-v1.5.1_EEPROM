void comms() {
  //delay(1000);
  ComsInput = "";
  while (mySerial.available() > 0) {
    ComsInput = mySerial.readStringUntil(':');
    Serial.print(F("ComsInput:  "));
    Serial.println(ComsInput);

    if (ComsInput == F("WRTSTN"))
    {
      time2run = mySerial.readStringUntil(':').toInt();
      waittime = mySerial.readStringUntil(':').toInt();
      directsunlight = mySerial.readStringUntil(':').toInt();
      daylightlevel = mySerial.readStringUntil(':').toInt();
      target_width = mySerial.readStringUntil(':').toInt();
      aim = mySerial.readStringUntil(':').toInt();
      String Backtrack_in = mySerial.readStringUntil(':');
      if (Backtrack_in == "true") {
        Allow_Backtrack = true;
      } else {
        Allow_Backtrack = false;
      }
	  eig = mySerial.readStringUntil(':').toInt();
	  wig = mySerial.readStringUntil('>').toInt();

    } else {
      int nullaim = mySerial.readStringUntil('>').toInt();
    }
    Parse_Input();
  }

  while (Serial.available() > 0) {
    //ComsInput = "";
    ComsInput = Serial.readStringUntil(':');
    //aim = Serial.readStringUntil('~').toInt();
    Serial.print(F("This is USB Input:  "));
    Serial.println(ComsInput);
    Parse_Input();
  }
  delay(10);
}
