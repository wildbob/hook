#pragma once
#include "menu.h"

c_menu* g_menu;


c_menu::c_menu()
{

	main_window = new c_window("", Vector(500, 500), Vector(600, 400), true);
	Sleep(200);


	this->initialized = true;
}

