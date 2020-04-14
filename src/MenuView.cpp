#include "MenuView.h"
//#include "../include/MenuView.h"

namespace reflow
{
	MenuView::MenuView(MenuModel& model, LiquidCrystal& newLcd)
		:
		m_model{model},
		m_lcd{newLcd}
	{
	}

	void MenuView::MenuViewInit() const
	{
		m_lcd.setCursor(0, 0);
		m_lcd.print("T:000C Tm:00.00C");
		m_lcd.setCursor(0, 1);
		m_lcd.print("Czas:00m00s   ");
		m_lcd.noCursor();
	}

	void MenuView::Update()
	{
		m_targetTemperature = m_model.GetTargetTemperature();
		m_currentTemperature = m_model.GetCurrentTemperature();
		m_timeSeconds = m_model.GetTimeSeconds();
		m_timeMinutes = m_model.GetTimeMinutes();

		UpdateTargetTemperatureLcd();
		UpdateCurrentTemperatureLcd();
		UpdateTimeMinutesLcd();
		UpdateTimeSecondsLcd();
	}

	void MenuView::UpdateTargetTemperatureLcd() const
	{
		m_lcd.setCursor(m_lcdTargetTemperaturePosition, m_lcdTargetTemperatureRow);
		m_lcd.print("000");
		if (m_targetTemperature <= 9)
		{
			m_lcd.setCursor(m_lcdTargetTemperaturePosition + 2, m_lcdTargetTemperatureRow);
			m_lcd.print(m_targetTemperature);
		}
		else if (m_targetTemperature <= 99)
		{
			m_lcd.setCursor(m_lcdTargetTemperaturePosition + 1, m_lcdTargetTemperatureRow);
			m_lcd.print(m_targetTemperature);
		}
		else
		{
			m_lcd.setCursor(m_lcdTargetTemperaturePosition, m_lcdTargetTemperatureRow);
			m_lcd.print(m_targetTemperature);
		}
	}

	void MenuView::UpdateCurrentTemperatureLcd() const
	{
		m_lcd.setCursor(m_lcdCurrentTemperaturePosition, m_lcdCurrentTemperatureRow);
		m_lcd.print(m_currentTemperature);
	}

	void MenuView::UpdateTimeMinutesLcd() const
	{
		m_lcd.setCursor(m_lcdTimeMinutesPosition, m_lcdTimeMinutesRow);
		m_lcd.print("00");
		if (m_timeMinutes <= 9)
		{
			m_lcd.setCursor(m_lcdTimeMinutesPosition + 1, m_lcdTimeMinutesRow);
			m_lcd.print(m_timeMinutes);
		}
		else
		{
			m_lcd.setCursor(m_lcdTimeMinutesPosition, m_lcdTimeMinutesRow);
			m_lcd.print(m_timeMinutes);
		}
	}

	void MenuView::UpdateTimeSecondsLcd() const
	{
		m_lcd.setCursor(m_lcdTimeSecondsPosition, m_lcdTimeSecondsRow);
		m_lcd.print("00");
		if (m_timeSeconds <= 9)
		{
			m_lcd.setCursor(m_lcdTimeSecondsPosition + 1, m_lcdTimeSecondsRow);
			m_lcd.print(m_timeSeconds);
		}
		else
		{
			m_lcd.setCursor(m_lcdTimeSecondsPosition, m_lcdTimeSecondsRow);
			m_lcd.print(m_timeSeconds);
		}
	}

	void MenuView::BlinkManager()
	{
		UpdateTargetTemperatureLcd();
		UpdateTimeMinutesLcd();
		UpdateTimeSecondsLcd();

		switch (m_model.IsBeingEdited())
		{
		case 1: // targetTemperature
			if (m_isVisibleBlink)
			{
				m_lcd.setCursor(m_lcdTargetTemperaturePosition, m_lcdTargetTemperatureRow);
				for (auto i = 1; i <= m_lcdTargetTemperatureLength; i++)
				{
					m_lcd.print(" ");
					m_lcd.setCursor(m_lcdTargetTemperaturePosition + i, m_lcdTargetTemperatureRow);
				}
			}
			else
			{
				UpdateTargetTemperatureLcd();
			}
			m_isVisibleBlink = !m_isVisibleBlink;
			break;

		case 2: // timeMinutes
			if (m_isVisibleBlink)
			{
				m_lcd.setCursor(m_lcdTimeMinutesPosition, m_lcdTimeMinutesRow);
				for (auto i = 1; i <= m_lcdTimeMinutesLength; i++)
				{
					m_lcd.print(" ");
					m_lcd.setCursor(m_lcdTimeMinutesPosition + i, m_lcdTimeMinutesRow);
				}
			}
			else
			{
				UpdateTimeMinutesLcd();
			}
			m_isVisibleBlink = !m_isVisibleBlink;
			break;

		case 3: // timeSeconds
			if (m_isVisibleBlink)
			{
				m_lcd.setCursor(m_lcdTimeSecondsPosition, m_lcdTimeSecondsRow);
				for (auto i = 1; i <= m_lcdTimeSecondsLength; i++)
				{
					m_lcd.print(" ");
					m_lcd.setCursor(m_lcdTimeSecondsPosition + i, m_lcdTimeSecondsRow);
				}
			}
			else
			{
				UpdateTimeSecondsLcd();
			}
			m_isVisibleBlink = !m_isVisibleBlink;
			break;
			
			default: ;
		}
	}
} // namespace reflow
