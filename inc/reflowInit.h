#pragma once

#include <LiquidCrystal.h>
#include "MenuView.h"

namespace reflow
{
	void Init(LiquidCrystal& lcd, MenuView& mc); // invokes init methods in lcd and menu, sets pins and their initial states

	void Init_SetPins(); //helper for init
	
} // namespace reflow
