void Parse_Input()
{
	if ((ComsInput != F("EST")) &&
		(ComsInput != F("WST")) &&
		(ComsInput != F("WND")) &&
		(ComsInput != F("S")) &&
		(ComsInput != F("HLL")) &&
		(ComsInput != F("T"))) {

		//DO WHAT IS NEEDED FOR SNDING BACK THE EEPROM DATA 

		if (ComsInput == F("SETTINGS")) {
			ReturnSettings();
		}

		if (ComsInput == F("WRTSTN")) {
			BurnEEPROM();
		}

	}
	else {
		delay(20);
		if ((ComsInput == F("EST")) && (Status != F("Hail")) && (Status != F("Wind"))) {
			Tracking = false;
			Track_East();
		}
		else if ((ComsInput == F("WND")) && (Status != F("Hail")) && (Status != F("Wind"))) {
			Tracking = false;
			//ComsInput = "S";
			Wind_Prep();
		}
		else if ((ComsInput == F("WST")) && (Status != F("Hail")) && (Status != F("Wind"))) {
			Tracking = false;
			Track_West();
		}
		else if ((ComsInput == F("S")) && (Status != F("Hail")) && (Status != F("Wind"))) {
			Tracking = false;
			FullStop();
		}
		else if ((ComsInput == F("HLL")) && (Status !=F("Hail")) && (Status !=F("Wind"))) {
			Tracking = false;
			Hail_Prep();
		}
		else if ((ComsInput ==F("T"))) {
			Status =F("prepped");
			Tracking = true;
		}
		else {
			// Tracking = false;
		}
	}
}
