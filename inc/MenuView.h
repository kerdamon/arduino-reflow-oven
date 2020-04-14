#pragma once

#include <LiquidCrystal.h>
#include "MenuModel.h"

namespace reflow {

	class MenuView
	{
	public:

		MenuView(MenuModel& model, LiquidCrystal &newLcd);

		void MenuViewInit() const;	// Set general/primary layout on lcd
		void Update();			// Updates View with information from Model
		void BlinkManager();	// Blinks targetTemperture, timeMinutes and timeSeconds. Uses their update methods.

	private:

		void UpdateTargetTemperatureLcd() const;
		void UpdateCurrentTemperatureLcd() const;
		void UpdateTimeMinutesLcd() const;
		void UpdateTimeSecondsLcd() const;

	//variables

		MenuModel& m_model;
		LiquidCrystal& m_lcd;

		bool m_isVisibleBlink = false;
		
		short m_targetTemperature = 0;
		float m_currentTemperature = 0;
			
		short m_timeSeconds = 0;
		short m_timeMinutes = 0;

		byte m_lcdTargetTemperaturePosition = 2;
		byte m_lcdTargetTemperatureRow = 0;
		byte m_lcdTargetTemperatureLength = 3;

		byte m_lcdCurrentTemperaturePosition = 10;
		byte m_lcdCurrentTemperatureRow = 0;
		byte m_lcdCurrentTemperatureLength = 5;

		byte m_lcdTimeMinutesPosition = 5;
		byte m_lcdTimeMinutesRow = 1;
		byte m_lcdTimeMinutesLength = 2;

		byte m_lcdTimeSecondsPosition = 8;
		byte m_lcdTimeSecondsRow = 1;
		byte m_lcdTimeSecondsLength = 2;

	}; // class MenuController

} // namespace reflow