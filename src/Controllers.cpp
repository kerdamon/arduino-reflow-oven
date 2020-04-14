#include "Controllers.h"
#include "Arduino.h"

#define CLR_BIT(ADDR, BIT) ((ADDR) &= ~(1 << (BIT)))
#define SET_BIT(ADDR, BIT) ((ADDR) |=  (1 << (BIT)))
#define TOG_BIT(ADDR, BIT) ((ADDR) ^=  (1 << (BIT)))
#define VALUE_BIT(ADDR, BIT) ((ADDR) & (1 << (BIT)))

namespace reflow
{
	//========================================
	// Keyboard
	//========================================

	KeyboardController::KeyboardController(MenuModel& model, MenuView& view, const int newKeyR0, const int newKeyR1,
		const int newKeyR2, const int newKeyC0, const int newKeyC1,
		const int newKeyC2)
		:
		m_model{ model },
		m_view{ view },
		m_keyPre{ 0xffff },
		m_keyAct{ 0xffff },
		m_keyR0{ newKeyR0 },
		m_keyR1{ newKeyR1 },
		m_keyR2{ newKeyR2 },
		m_keyC0{ newKeyC0 },
		m_keyC1{ newKeyC1 },
		m_keyC2{ newKeyC2 }
	{
	}

	void KeyboardController::WatchForInput()
	{
		m_keyPre = m_keyAct;	//pre is used for press vs hold recognition
		m_keyAct = 0xffff;

		digitalWrite(m_keyR0, LOW);
		if (!digitalRead(m_keyC0))
			CLR_BIT(m_keyAct, m_keyI100);
		if (analogRead(m_keyC1) < 128)
			CLR_BIT(m_keyAct, m_keyI10);
		if (analogRead(m_keyC2) < 128)
			CLR_BIT(m_keyAct, m_keyI1);
		digitalWrite(m_keyR0, HIGH);

		digitalWrite(m_keyR1, LOW);
		if (!digitalRead(m_keyC0))
			CLR_BIT(m_keyAct, m_keyStop);
		if (analogRead(m_keyC1) < 128)
			CLR_BIT(m_keyAct, m_keySelect);
		if (analogRead(m_keyC2) < 128)
			CLR_BIT(m_keyAct, m_keyRun);
		digitalWrite(m_keyR1, HIGH);

		digitalWrite(m_keyR2, LOW);
		if (!digitalRead(m_keyC0))
			CLR_BIT(m_keyAct, m_keyD100);
		if (analogRead(m_keyC1) < 128)
			CLR_BIT(m_keyAct, m_keyD10);
		if (analogRead(m_keyC2) < 128)
			CLR_BIT(m_keyAct, m_keyD1);
		digitalWrite(m_keyR2, HIGH);

		bool update = false;
		if (VALUE_BIT(m_keyPre, m_keyI100) && !VALUE_BIT(m_keyAct, m_keyI100))
		{
			m_model.PressedKey(MenuModel::KeyNames::kI100);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyI10) && !VALUE_BIT(m_keyAct, m_keyI10))
		{
			m_model.PressedKey(MenuModel::KeyNames::kI10);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyI1) && !VALUE_BIT(m_keyAct, m_keyI1))
		{
			m_model.PressedKey(MenuModel::KeyNames::kI1);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyStop) && !VALUE_BIT(m_keyAct, m_keyStop))
		{
			m_model.PressedKey(MenuModel::KeyNames::kStop);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keySelect) && !VALUE_BIT(m_keyAct, m_keySelect))
		{
			m_model.PressedKey(MenuModel::KeyNames::kSelect);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyRun) && !VALUE_BIT(m_keyAct, m_keyRun))
		{
			m_model.PressedKey(MenuModel::KeyNames::kRun);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyD100) && !VALUE_BIT(m_keyAct, m_keyD100))
		{
			m_model.PressedKey(MenuModel::KeyNames::kD100);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyD10) && !VALUE_BIT(m_keyAct, m_keyD10))
		{
			m_model.PressedKey(MenuModel::KeyNames::kD10);
			update = true;
		}
		if (VALUE_BIT(m_keyPre, m_keyD1) && !VALUE_BIT(m_keyAct, m_keyD1))
		{
			m_model.PressedKey(MenuModel::KeyNames::kD1);
			update = true;
		}
		if (update)
			m_view.Update();
	}

	//========================================
	// Temperature
	//========================================

	TemperatureController::TemperatureController(MenuModel& model, MenuView& view)
		:
		m_model{ model },
		m_view{ view }
	{
	}

	void TemperatureController::UpdateTemperature()
	{
		m_model.SetCurrentTemperature(m_thermocouple.readCelsius());
		CheckIfReady();
		m_view.Update();
	}

	void TemperatureController::CheckIfReady() const
	{
		if (m_model.IsOvenWorking() && !m_model.IsOvenReady() && m_model.GetCurrentTemperature() >= static_cast<float>(m_model.GetTargetTemperature()))
		{
			m_model.SetOvenReady();
		}
		
		if (m_model.IsOvenWorking() && (m_model.GetTargetTemperature() - m_model.GetCurrentTemperature()) > m_unreadyOffset)
		{
			m_model.SetOvenNotReady();
		}
	}

} // namespace reflow