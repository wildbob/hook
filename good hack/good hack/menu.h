#pragma once
#include "basecontrol.h"
#include "window.h"

class c_menu
{
public:
	c_menu();

	void SaveWindowState(std::string Filename);
	void LoadWindowState(std::string Filename);
	float alpha = 0;
	c_window* main_window = nullptr;
	bool initialized = false;

}; extern c_menu* g_menu;
