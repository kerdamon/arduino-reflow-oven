#include "MenuModel.h"
#include "Heater.h"
#include "driver.h"
//#include "../include/MenuModel.h"
//#include "../include/driver.h"
//#include "../include/Heater.h"

namespace reflow
{
	MenuModel::MenuModel(const short newMaxTemperature, const short newMinTemperature, const short newMaxTimeMinutes,
	                     const short newMinTimeMinutes, const short newMaxTimeSeconds, const short newMinTimeSeconds)
		:
		m_maxTargetTemperature{newMaxTemperature},
		m_minTargetTemperature{newMinTemperature},
		m_maxTimeSeconds{newMaxTimeSeconds},
		m_minTimeSeconds{newMinTimeSeconds},
		m_maxTimeMinutes{newMaxTimeMinutes},
		m_minTimeMinutes{newMinTimeMinutes}
	{
	}

	void MenuModel::PressedKey(const KeyNames keyIndex)
	{
		switch (keyIndex)
		{
		case KeyNames::kI100:
			PressedKey_kI100();
			break;

		case KeyNames::kI10:
			PressedKey_kI10();
			break;

		case KeyNames::kI1:
			PressedKey_kI1();
			break;

		case KeyNames::kStop:
			PressedKey_kStop();
			break;

		case KeyNames::kSelect:
			PressedKey_kSelect();
			break;

		case KeyNames::kRun:
			PressedKey_kRun();
			break;

		case KeyNames::kD100:
			PressedKey_kD100();
			break;

		case KeyNames::kD10:
			PressedKey_kD10();
			break;

		case KeyNames::kD1:
			PressedKey_kD1();
			break;

		default: ;
		}
	}

	void MenuModel::SetOvenReady()
	{
		m_isOvenReady = true;
	}

	void MenuModel::SetOvenNotReady()
	{
		m_isOvenReady = false;
		m_isTimerWorking = false;
	}

	void MenuModel::SetTimerWorking()
	{
		m_isTimerWorking = true;
	}

	void MenuModel::SetTimerNotWorking()
	{
		m_isTimerWorking = false;
	}

	void MenuModel::FanSwitch()
	{
		if (m_isFanWorking)
		{
			m_isFanWorking = false;
			TurnOffFan();
		}
		else
		{
			m_isFanWorking = true;
			TurnOnFan();
		}
	}

	void MenuModel::DecreaseTimer_1Sec()
	{
		if (m_isOvenWorking)
		{
			if (m_timeSeconds <= 0 && m_timeMinutes <= 0)
			{
				StopOven();
			}
			else if (m_timeSeconds <= 0)
			{
				DecrementValue(m_timeMinutes, 1, m_minTimeSeconds);
				m_timeSeconds = static_cast<short>(m_maxTimeSeconds - 1);
			}
			else
				DecrementValue(m_timeSeconds, 1, m_minTimeSeconds);
		}
	}

	void MenuModel::UpdateReadyIndicator()
	{
		//if oven not ready 
		//blink led
		//else if is not timer working 
		//turn on led
		//else
		//turn off led
		if (!IsOvenReady())
			RedLedSwitch();
		else if (!IsTimerWorking())
			SetLED_R();
		else
			ClearLED_R();
	}

	void MenuModel::StopOven()
	{
		m_isOvenWorking = false;
		Heater::OvenStop();
	}

	void MenuModel::RunOven()
	{
		m_isOvenWorking = true;
	}

	void MenuModel::RedLedSwitch()
	{
		if (m_redLedBlinkIsVisible)
		{
			m_redLedBlinkIsVisible = false;
			ClearLED_R();
		}
		else
		{
			m_redLedBlinkIsVisible = true;
			SetLED_R();
		}
	}

	void MenuModel::SetCurrentTemperature(const float newCurrentTemperature)
	{
		m_currentTemperature = newCurrentTemperature;
	}

	void MenuModel::SetTargetTemperature(const short newTargetTemperature)
	{
		m_targetTemperature = newTargetTemperature;
	}

	//private methods

	void MenuModel::PressedKey_kI100()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				IncrementValue(m_targetTemperature, 100, m_maxTargetTemperature);
				break;

			case 2:
				IncrementValue(m_timeMinutes, 100, m_maxTimeMinutes);
				break;

			case 3:
				IncrementValue(m_timeSeconds, 100, m_maxTimeSeconds);
				break;

			default: ;
			}
	}

	void MenuModel::PressedKey_kI10()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				IncrementValue(m_targetTemperature, 10, m_maxTargetTemperature);
				break;

			case 2:
				IncrementValue(m_timeMinutes, 10, m_maxTimeMinutes);
				break;

			case 3:
				IncrementValue(m_timeSeconds, 10, m_maxTimeSeconds);
				break;

			default: ;
			}
	}

	void MenuModel::PressedKey_kI1()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				IncrementValue(m_targetTemperature, 1, m_maxTargetTemperature);
				break;

			case 2:
				IncrementValue(m_timeMinutes, 1, m_maxTimeMinutes);
				break;

			case 3:
				IncrementValue(m_timeSeconds, 1, m_maxTimeSeconds);
				break;

			default:
				SetNextPredefinedValues();
				break;
			}
	}

	void MenuModel::PressedKey_kStop()
	{
		StopOven();
	}

	void MenuModel::PressedKey_kSelect()
	{
		StopOven();
		SwitchEditMode();
	}

	void MenuModel::PressedKey_kRun()
	{
		if (!m_isBeingEdited)
			RunOven();
		if (m_isOvenWorking && m_isOvenReady && !m_isTimerWorking)
			m_isTimerWorking = true;
	}

	void MenuModel::PressedKey_kD100()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				DecrementValue(m_targetTemperature, 100, m_minTargetTemperature);
				break;

			case 2:
				DecrementValue(m_timeMinutes, 100, m_minTimeMinutes);
				break;

			case 3:
				DecrementValue(m_timeSeconds, 100, m_minTimeSeconds);
				break;

			default:
				FanSwitch();
				break;
			}
	}

	void MenuModel::PressedKey_kD10()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				DecrementValue(m_targetTemperature, 10, m_minTargetTemperature);
				break;

			case 2:
				DecrementValue(m_timeMinutes, 10, m_minTimeMinutes);
				break;

			case 3:
				DecrementValue(m_timeSeconds, 10, m_minTimeSeconds);
				break;

			default: ;
			}
	}

	void MenuModel::PressedKey_kD1()
	{
		if (!m_isOvenWorking)
			switch (m_isBeingEdited)
			{
			case 1:
				DecrementValue(m_targetTemperature, 1, m_minTargetTemperature);
				break;

			case 2:
				DecrementValue(m_timeMinutes, 1, m_minTimeMinutes);
				break;

			case 3:
				DecrementValue(m_timeSeconds, 1, m_minTimeSeconds);
				break;

			default:
				SetPreviousPredefinedValues();
				break;
			}
	}

	void MenuModel::IncrementValue(short& incrementedValue, const short increment, const short maxValue)
	{
		incrementedValue = static_cast<short>(incrementedValue + increment);
		if (incrementedValue > maxValue)
			incrementedValue = maxValue;
	}

	void MenuModel::DecrementValue(short& decrementedValue, const short decrement, const short minValue)
	{
		decrementedValue = static_cast<short>(decrementedValue - decrement);
		if (decrementedValue < minValue)
			decrementedValue = minValue;
	}

	void MenuModel::SetNextPredefinedValues()
	{
		for (auto i = 0; i < m_predefinedTemperaturesLength; i++)
		{
			if (m_predefinedTemperatures[i] > m_targetTemperature)
			{
				m_targetTemperature = m_predefinedTemperatures[i];
				break;
			}
		}

		for (auto i = 0; i < m_predefinedTimeMinutesLength; i++)
		{
			if (m_predefinedTimeMinutes[i] > m_timeMinutes)
			{
				m_timeMinutes = m_predefinedTimeMinutes[i];
				break;
			}
		}
	}

	void MenuModel::SetPreviousPredefinedValues()
	{
		for (int i = m_predefinedTemperaturesLength - 1; i >= 0; i--)
		{
			if (m_predefinedTemperatures[i] < m_targetTemperature)
			{
				m_targetTemperature = m_predefinedTemperatures[i];
				break;
			}
		}

		for (int i = m_predefinedTimeMinutesLength - 1; i >= 0; i--)
		{
			if (m_predefinedTimeMinutes[i] < m_timeMinutes)
			{
				m_timeMinutes = m_predefinedTimeMinutes[i];
				break;
			}
		}
	}

	void MenuModel::SwitchEditMode()
	{
		m_isBeingEdited = ++m_isBeingEdited % (m_howManySettableValues + 1);
	}
} // namespace reflow
