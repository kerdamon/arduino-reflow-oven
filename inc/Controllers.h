#pragma once

#include <max6675.h>
#include "driver.h"
#include "MenuModel.h"
#include "MenuView.h"

namespace reflow {
	
	//========================================
	// Keyboard
	//========================================
	
	class KeyboardController{
	public:
		
		KeyboardController(MenuModel& model, MenuView& view, int newKeyR0, int newKeyR1, int
		                   newKeyR2, int newKeyC0, int newKeyC1, int newKeyC2);
		
		void WatchForInput();		// Gets input from pins.
		
	private:
	
		MenuModel& m_model;
		MenuView& m_view;
	
		unsigned int m_keyPre;
		unsigned int m_keyAct;
		
		const int m_keyR0;
		const int m_keyR1;
		const int m_keyR2;
		const int m_keyC0;
		const int m_keyC1;
		const int m_keyC2;
		
		const int m_keyI100 = 0;
		const int m_keyI10 = 1;
		const int m_keyI1 = 2;
		const int m_keyStop = 3;
		const int m_keySelect = 4;
		const int m_keyRun = 5;
		const int m_keyD100 = 6;
		const int m_keyD10 = 7;
		const int m_keyD1 = 8;
	
	};	// class Keyboard
	
	//========================================
	// Temperature
	//========================================
	
	class TemperatureController{
	public:
	
		TemperatureController(MenuModel& model, MenuView& view);
		
		void UpdateTemperature();	//Reads current temperature from thermocouple, and saves it to model.
	
	private:
	
		MenuModel& m_model;
		MenuView& m_view;
		
		short m_unreadyOffset = 20;
	
		void CheckIfReady() const;
	
		MAX6675 m_thermocouple{ PIN_MAX6675_CLK, PIN_MAX6675_CS, PIN_MAX6675_DO };
	};
	
} // namespace reflow

