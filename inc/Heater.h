#pragma once

#include <Arduino.h>

namespace reflow {

	class Heater
	{
	public:

		void UpdateHeat(float currentTemperature, short targetTemperature, bool isOvenWorking = true);	// Manages heater. Main function of HeatController. 
		static void OvenStop();	//Turns down heater, safe switch to turn down heat immediately.
		
		byte GetPhaseFilling() const { return m_phaseFilling; }
	
	private:

		void SetPhaseFilling(float currentTemperature, short targetTemperature);
		void ManageHeatPower();
		static void HeatOn();
		static void HeatOff();

		const float m_multiplyingParameter = 2;
		
		byte m_phaseFilling = 0;
		const short m_maxPhaseFilling = 100;
		
		byte m_phaseIterator = 0;
		const short m_maxPhaseIterator = 100;
		
	
	}; //HeatController

} // namespace reflow