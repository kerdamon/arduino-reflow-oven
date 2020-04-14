#include "Heater.h"
#include "driver.h"
//#include "../include/Heater.h"
//#include "../include/driver.h"

namespace reflow {
	
	void Heater::UpdateHeat(const float currentTemperature, const short targetTemperature, bool isOvenWorking)
	{
		if (isOvenWorking) {
			SetPhaseFilling(currentTemperature, targetTemperature);
			ManageHeatPower();
		}
		else
		{
			m_phaseFilling = 0;
			HeatOff();
		}
	}

	void Heater::SetPhaseFilling(const float currentTemperature, const short targetTemperature)
	{
		const float diff = static_cast<float>(targetTemperature) - currentTemperature;
		
		if(diff >= 50)
			m_phaseFilling = m_maxPhaseFilling;
		else if(diff > 0)
		{
			float newPhase = diff * m_multiplyingParameter;
			auto tempMaxPhaseFilling = m_maxPhaseFilling;
			if(diff < 15) tempMaxPhaseFilling = 20;
			if(newPhase > static_cast<float>(tempMaxPhaseFilling)) newPhase = tempMaxPhaseFilling ;
			m_phaseFilling = newPhase;
		}
		else {
			m_phaseFilling = 0;
		}
	}

	void Heater::ManageHeatPower()
	{
		if (m_phaseFilling)
		{
			if (m_phaseIterator++ <= m_phaseFilling)
				HeatOn();
			else
				HeatOff();
			if(m_phaseIterator > m_maxPhaseIterator) m_phaseIterator = 0;
		}
		else {
			HeatOff();
			m_phaseIterator = 0;
		}
	}

	void Heater::OvenStop()
	{
		HeatOff();
	}

	void Heater::HeatOn()
	{
		SetTriac();
		SetLED_B();
	}

	void Heater::HeatOff()
	{
		ClearTriac();
		ClearLED_B();
	}

} // namespace reflow