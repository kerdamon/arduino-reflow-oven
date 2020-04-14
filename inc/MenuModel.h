#pragma once

#include <Arduino.h>

namespace reflow{
	class MenuModel
	{
	public:

		explicit MenuModel(short newMaxTemperature = 900, short newMinTemperature = 0,
		                   short newMaxTimeMinutes = 99, short newMinTimeMinutes = 0,
		                   short newMaxTimeSeconds = 60, short newMinTimeSeconds = 0);
		
		enum class KeyNames { kAnyKey, kI100, kI10, kI1, kStop, kSelect, kRun, kD100, kD10, kD1 };
	
		void PressedKey(KeyNames keyIndex);	// Invokes private method corresponding to pressed key

		void FanSwitch();	// Alternately turns fan on or off
		void DecreaseTimer_1Sec();
		void RedLedSwitch();	// Alternately turns red led on or off
		void UpdateReadyIndicator();	// Blinks when not ready, glows constantly when timer is ready to start.

		//setters
		void StopOven();
		void RunOven();
		void SetCurrentTemperature(float newCurrentTemperature);
		void SetTargetTemperature(short newTargetTemperature);
		void SetOvenReady();
		void SetOvenNotReady();
		void SetTimerWorking();
		void SetTimerNotWorking();

		//getters
		float GetCurrentTemperature() const { return m_currentTemperature; }
		short GetTargetTemperature() const { return m_targetTemperature; }
		short GetTimeSeconds() const { return m_timeSeconds; }
		short GetTimeMinutes() const { return m_timeMinutes; }
		bool IsOvenWorking() const { return m_isOvenWorking; }
		byte IsBeingEdited() const { return m_isBeingEdited; }
		bool IsOvenReady() const { return m_isOvenReady; }
		bool IsTimerWorking() const { return m_isTimerWorking; }

	private:
	
		//private methods
				
		void PressedKey_kI100();
		void PressedKey_kI10();
		void PressedKey_kI1();
		void PressedKey_kStop();
		void PressedKey_kSelect();
		void PressedKey_kRun();
		void PressedKey_kD100();
		void PressedKey_kD10();
		void PressedKey_kD1();

		static void IncrementValue(short &incrementedValue, const short increment, const short maxValue);
		static void DecrementValue(short &decrementedValue, const short decrement, const short minValue);
				
		void SetNextPredefinedValues();
		void SetPreviousPredefinedValues();
				
		void SwitchEditMode();
	
		//private variables
	
		bool m_isOvenWorking = false;
		bool m_isOvenReady = false;
		bool m_isTimerWorking = false;
		bool m_isFanWorking = false;
		byte m_isBeingEdited = 0;
		bool m_redLedBlinkIsVisible = false;
	
		float m_currentTemperature = 0;
		short m_targetTemperature = 0;

		const short m_maxTargetTemperature;
		const short m_minTargetTemperature;
		
		const byte m_predefinedTemperaturesLength = 3;
		const byte m_predefinedTimeMinutesLength = 3;
		const short m_predefinedTemperatures[3] {0, 70, 150};
		const short m_predefinedTimeMinutes[3] {0, 40, 60};
		
		short m_timeSeconds = 0;
		const short m_maxTimeSeconds;
		const short m_minTimeSeconds;
		short m_timeMinutes = 0;
		const short m_maxTimeMinutes;
		const short m_minTimeMinutes;
		
		byte m_howManySettableValues = 3;
		
	}; // Class Controller
	
} // namespace reflow