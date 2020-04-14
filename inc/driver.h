#pragma once

#include <Arduino.h>

namespace reflow {

	//========================================
	// PIN definitions:
	//========================================
	
	// display
	const int PIN_LCD_RS = 10;
	const int PIN_LCD_EN = 12;
	const int PIN_LCD_D4 = 8;
	const int PIN_LCD_D5 = A4;
	const int PIN_LCD_D6 = A2;
	const int PIN_LCD_D7 = A0;

	// thermocouple
	const int PIN_MAX6675_DO = 7;
	const int PIN_MAX6675_CS = 6;
	const int PIN_MAX6675_CLK = 5;

	//keypad
	const int PIN_KEY_R0=13;
	const int PIN_KEY_R1=A1;
	const int PIN_KEY_R2=A3;
	const int PIN_KEY_C0=A5;
	const int PIN_KEY_C1=A7;
	const int PIN_KEY_C2=A6;

	const int PIN_RELAY = 3;
	const int PIN_TRIAC = 4;
	const int PIN_LED_R = 9;
	const int PIN_LED_B = 11;

	//pin for triac interruption when voltage reaches 0
	const int PIN_INT0_PIN = 2;

	//========================================
	// hardware methods:
	//========================================
	
	void ClearTriac ();
	void SetTriac ();
	void TurnOffFan ();
	void TurnOnFan ();
	void ClearLED_R	();
	void SetLED_R ();
	void ClearLED_B	();
	void SetLED_B ();
	
} // namespace reflow