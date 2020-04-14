#include "Arduino.h"
#include "driver.h"
//#include "../arduinoCore/include/core/Arduino.h"
//#include "../include/driver.h"

namespace reflow
{
	void ClearTriac (){
		digitalWrite(PIN_TRIAC, HIGH);
	}

	void SetTriac (){
		digitalWrite(PIN_TRIAC, LOW);
	}

	void TurnOffFan (){
		digitalWrite(PIN_RELAY, LOW);
	}

	void TurnOnFan (){
		digitalWrite(PIN_RELAY, HIGH);
	}

	void ClearLED_R	(){
		digitalWrite(PIN_LED_R, HIGH);
	}

	void SetLED_R (){
		digitalWrite(PIN_LED_R, LOW);
	}

	void ClearLED_B	(){
		digitalWrite(PIN_LED_B, HIGH);
	}

	void SetLED_B (){
		digitalWrite(PIN_LED_B, LOW);
	}
	
} // namespace reflow