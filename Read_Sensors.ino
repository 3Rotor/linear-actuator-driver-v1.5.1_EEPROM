void Read_Sensors() {

//mic03
    //here we take an average over 30 readings to smooth out the resultant
    //time inteval for each adjustment
    ALE_total = ALE_total - ALE_readings[ALE_arrayIndex];
    ALE_readings[ALE_arrayIndex] = analogRead(0);
    ALE_total = ALE_total + ALE_readings[ALE_arrayIndex];
    ALE_arrayIndex += 1;
    // At the end of the array (10 items) then start again
    if (ALE_arrayIndex >= ALE_AC)ALE_arrayIndex = 0;
    ALE = ALE_total / (ALE_AC-0);

    //here we take an average over 30 readings to smooth out the resultant
    //time inteval for each adjustment
    ALW_total = ALW_total - ALW_readings[ALW_arrayIndex];
    ALW_readings[ALW_arrayIndex] = analogRead(2);
    ALW_total = ALW_total + ALW_readings[ALW_arrayIndex];
    ALW_arrayIndex += 1;
    // At the end of the array (10 items) then start again
    if (ALW_arrayIndex >= ALW_AC)ALW_arrayIndex = 0;
    ALW = ALW_total / (ALW_AC-0);

    PR = ALW - ALE;
    Ambient_Light = ALE + ALW;

}
