void Parse_Input()
{
	if ((ComsInput != "EST") &&
		(ComsInput != "WST") &&
		(ComsInput != "WND") &&
		(ComsInput != "S") &&
		(ComsInput != "HLL") &&
		(ComsInput != "T")) {

		//DO WHAT IS NEEDED FOR SNDING BACK THE EEPROM DATA 

		if (ComsInput == "SETTINGS") {

			ReturnSettings();



		}
		if (ComsInput == "WRTSTN") {

			BurnEEPROM();



		}



	}
	else {
		delay(20);
		if ((ComsInput == "EST") && (Status != "Hail") && (Status != "Wind")) {
			Tracking = false;
			Track_East();
		}
		else if ((ComsInput == "WND") && (Status != "Hail") && (Status != "Wind")) {
			Tracking = false;
			//ComsInput = "S";
			Wind_Prep();
		}
		else if ((ComsInput == "WST") && (Status != "Hail") && (Status != "Wind")) {
			Tracking = false;
			Track_West();
		}
		else if ((ComsInput == "S") && (Status != "Hail") && (Status != "Wind")) {
			Tracking = false;
			FullStop();
		}
		else if ((ComsInput == "HLL") && (Status != "Hail") && (Status != "Wind")) {
			Tracking = false;
			Hail_Prep();
		}
		else if ((ComsInput == "T")) {
			Status = "prepped";
			Tracking = true;
		}
		else {
			// Tracking = false;
		}
	}
}
