#include "reflowInit.h"
#include "driver.h"

namespace reflow
{
	void Init(LiquidCrystal& lcd, MenuView& mc)
	{
		lcd.begin(16, 2);
		lcd.clear();

		mc.MenuViewInit();

		Init_SetPins();

		//initial pin states
		digitalWrite(PIN_KEY_R0, HIGH);
		digitalWrite(PIN_KEY_R1, HIGH);
		digitalWrite(PIN_KEY_R2, HIGH);

		digitalWrite(PIN_LED_R, HIGH);
		digitalWrite(PIN_LED_B, HIGH);
		digitalWrite(PIN_RELAY, LOW);
		digitalWrite(PIN_TRIAC, HIGH);
	}

	void Init_SetPins()
	{
		//keyboard
		pinMode(PIN_KEY_R0, OUTPUT);
		pinMode(PIN_KEY_R1, OUTPUT);
		pinMode(PIN_KEY_R2, OUTPUT);
		pinMode(PIN_KEY_C0, INPUT_PULLUP);
		pinMode(PIN_KEY_C1, INPUT);
		pinMode(PIN_KEY_C2, INPUT_PULLUP);

		pinMode(PIN_INT0_PIN, INPUT_PULLUP); // enter into interrupt

		pinMode(PIN_LED_R, OUTPUT);
		pinMode(PIN_LED_B, OUTPUT);
		pinMode(PIN_RELAY, OUTPUT);
		pinMode(PIN_TRIAC, OUTPUT);
	}
	
} // namespace reflow
