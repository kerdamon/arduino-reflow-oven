#include <Arduino.h>
#include "MenuModel.h"
#include "MenuView.h"
#include "Heater.h"
#include "Controllers.h"
#include "reflowInit.h"
#include "driver.h"

//========================================
// Instances of classes
//========================================
LiquidCrystal lcd(reflow::PIN_LCD_RS, reflow::PIN_LCD_EN, reflow::PIN_LCD_D4, reflow::PIN_LCD_D5, reflow::PIN_LCD_D6, reflow::PIN_LCD_D7);
reflow::Heater heater;
reflow::MenuModel model;
reflow::MenuView view(model, lcd);
reflow::TemperatureController temperatureController(model, view);
reflow::KeyboardController keyboardController(model, view, reflow::PIN_KEY_R0, reflow::PIN_KEY_R1, reflow::PIN_KEY_R2,
                                              reflow::PIN_KEY_C0, reflow::PIN_KEY_C1, reflow::PIN_KEY_C2);

void Int0Handler();
void printCurrentDataToSerial();

void setup()
{
	reflow::Init(lcd, view);
	attachInterrupt(digitalPinToInterrupt(2), Int0Handler, FALLING);
	Serial.begin(9600);
}

unsigned long currentTime = 0;
unsigned char t500msek = 0;
unsigned char t250msek = 0;
unsigned char t1sek = 0;
unsigned char t10sek = 0;

void loop()
{
	if (millis() - currentTime >= 50) // If for invoking everything in right order
	{
		currentTime = millis();

		keyboardController.WatchForInput();

		if (t10sek++ >= 200)
		{
			printCurrentDataToSerial();
			t10sek = 0;
		}

		if (t1sek++ >= 20)
		{
			if (model.IsTimerWorking())
				model.DecreaseTimer_1Sec();
			t1sek = 0;
		}

		if (t500msek++ >= 10)
		{
			temperatureController.UpdateTemperature();
			t500msek = 0;
		}

		if (t250msek++ >= 5)
		{
			view.BlinkManager();
			model.UpdateReadyIndicator();
			t250msek = 0;
		}
	}
}

void Int0Handler()
{
	heater.UpdateHeat(model.GetCurrentTemperature(), model.GetTargetTemperature(), model.IsOvenWorking());
}

void printCurrentDataToSerial()
{
	Serial.print(model.GetTargetTemperature());
	Serial.print(" ");
	Serial.print(model.GetCurrentTemperature());
	Serial.print(" ");
	Serial.print(heater.GetPhaseFilling());
	Serial.print("\n");
}