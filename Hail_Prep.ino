void Hail_Prep()
{
  if (Status != "Hail") {
    Serial.println(" Prepping for Hail.");
    Serial.println(" Please strap the Panel down to the base");
    Serial.println(" On all 4 corners.");
    Status = "Hail";
    Tracking = false;
    delay(20);

    long ttt = millis();
    while ((millis() < ttt + 95000)) {
      Serial.print(" Prepping for Hail. pulling panel East : ");
      Serial.println(ttt + 95000 - millis());
      while (mySerial.available() > 0) {
        ComsInput =  mySerial.readStringUntil(':');
        New_Aim = mySerial.readStringUntil('>').toInt();
        aim = map(New_Aim, 0, 100, -20, 20);
        Parse_Input();
      }
      if (Status == "prepped") break;

      Track_East();
      Show_Telemetry(ttt + 95000 - millis());

    }
    FullStop();
  }
}

